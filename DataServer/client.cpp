#include "common.h"
#include "BoundedBuffer.h"
#include "Histogram.h"
#include "common.h"
#include "HistogramCollection.h"
#include "NRC.h"
#include <stdio.h>
#include <fstream>

using namespace std;

void * patient_function(BoundedBuffer* buf, int n, int p, string file, __int64_t fileLen) {
  if(file == "") {
    for(int i = 0; i < n; i++) {
      double time = i * 0.004;
      datamsg* data = new datamsg(p, time, 1);
      char* temp = (char*) data;
      vector<char> dataMsg = vector<char>(temp, temp + sizeof(datamsg));
      buf->push(dataMsg);
    }
  }
  else {
    size_t found = file.find(".");
    string actualFile = file.substr(0, found);
    char buffer[sizeof(filemsg) + file.length() + 1];
    filemsg fileMsg(0, 0);
    memcpy(&buffer, &fileMsg, sizeof(fileMsg));
    strcpy(buffer + sizeof(fileMsg), file.c_str());
    string transferFile = "received/y" + file;
    ofstream requestFile;
    requestFile.open(transferFile, fstream::out | fstream::binary);
    fileMsg.length = MAX_MESSAGE;
    memcpy(&buffer, &fileMsg, sizeof(fileMsg));
    for(int i = 0; i < ceil(fileSize/(double)MAX_MESSAGE); i++) {
      if(fileMsg.offset + MAX_MESSAGE > fileSize) {
        fileMsg.length = fileSize - fileMsg.offset;
        memcpy(&buffer, &fileMsg, sizeof(fileMsg));
      }
      vector<char> fileReq = vector<char>((char*)&buffer, (char*)&buffer + sizeof(buffer));
      fileMsg.offset = fileMsg.offset + MAX_MESSAGE;
      memcpy(&buffer, &fileMsg, sizeof(fileMsg));
      buf->push(fileReq);
    }
    requestFile.close();
  }
}

void * worker_function(BoundedBuffer* buf, NRC* patientChan, HistogramCollection* h, string file) {
  size_t found = file.find(".");
  string actualFile = file.substr(0, found);
  string fileName = "received/y" + file;
  int fd = open(fileName.c_str(),  O_WRONLY, 0777);
  while(true) {
    vector<char> dataMsg = buf->pop();
    char* MsgCharPtr = reinterpret_cast<char*>(dataMsg.data());
    MESSAGE_TYPE message = *(MESSAGE_TYPE*)MsgCharPtr;
    if(message == DATA_MSG) {
      datamsg* dataMessage = (datamsg*)MsgCharPtr;
      patientChan->cwrite((char*)dataMessage, (int)sizeof(datamsg));
      char* dataMessagePtr = patientChan->cread();
      double dataPoint = *(double*) dataMessagePtr;

      h->update(dataMessage->person, dataPoint);
    }
    else if(message == FILE_MSG) {
      filemsg* f = (filemsg*)MsgCharPtr;

      string fileMessage = MsgCharPtr + sizeof(filemsg);
      patientChan->cwrite(MsgCharPtr, sizeof(filemsg) + fileMessage.length() + 1);
      char* fileMsgCharPtr = patientChan->cread();
      lseek(fd, f->offset, SEEK_SET);
      write(fd, fileMsgCharPtr, f->length);
    }
    else if(message == QUIT_MSG) {
      patientChan->cwrite((char*)&message, sizeof(QUIT_MSG));
      delete patientChan;
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  int n = 100;    //default number of requests per "patient"
  int p = 10;     // number of patients [1,15]
  int w = 100;    //default number of worker threads
  int b = 100; 	// default capacity of the request buffer, you should change this default
  int m = MAX_MESSAGE; 	// default capacity of the file buffer

  srand(time_t(NULL));

  string fileName = "";
  int c;
  string name;
  string port;
  try {
    while((c = getopt(argc, argv, "n:p:w:b:f:h:r:")) != -1) {
      switch (c) {
        case 'n':
        n = atoi(optarg);
        break;
        case 'p':
        p = atoi(optarg);
        break;
        case 'w':
        w = atoi(optarg);
        break;
        case 'b':
        b = atoi(optarg);
        break;
        case 'f':
        fileName = optarg;
        break;
        case 'h':
        name = optarg;
        break;
        case 'r':
        port = optarg;
        break;
        case '?':
        cout << "Error: Invalid Arguments" << endl;
        break;
      }
    }
  }
  catch(...) {
    cout << "Error: Trying Defaults" << endl;
  }

  BoundedBuffer request_buffer(b);
  HistogramCollection hc;
  vector<thread> patientThread;
  vector<thread> workerThread;
  vector<NRC*> channelNames;

  struct timeval start, end;
  gettimeofday (&start, 0);

  for(int i = 0; i < w; i++) {
    NRC* testChannel = new NRC(name, port);
    channelNames.push_back(testChannel);
  }

  __int64_t fileLength;
  if(fileName != "") {
    NRC* chan = new NRC(name,port);
    char buffer[sizeof(filemsg) + fileName.length() + 1];

    filemsg nullMsg(0, 0);

    memcpy(&buffer, &nullMsg, sizeof(nullMsg));
    strcpy(buffer + sizeof(nullMsg), fileName.c_str());
    chan->cwrite(buffer, sizeof(filemsg) + fileName.length() + 1);

    fileLength = *((__int64_t*)chan->cread());
    MESSAGE_TYPE q = QUIT_MSG;
    chan->cwrite ((char *) &q, sizeof (MESSAGE_TYPE));
  }

  for(int i = 0; i < p; i++) {
    thread th(patient_function, &request_buffer, n, i + 1, fileName, fileLength);
    patientThread.push_back(move(th));
    Histogram* newHist = new Histogram(10, -2.0, 2.0);
    hc.add(newHist);
  }

  for(int i = 0; i < w; i++) {
    thread th(worker_function, &request_buffer, channelNames.at(i), &hc, fileName);
    workerThread.push_back(move(th));
  }

  for(int i = 0; i < p; i++) {
    patientThread.at(i).join();
  }

  for(int i = 0; i < w; i++) {
    datamsg* quitMessage = new datamsg(1, 0, 1);
    quitMessage->mtype = QUIT_MSG;

    char* quitMsg = (char*) quitMessage;
    vector<char> quitData = vector<char>(quitMsg, quitMsg + sizeof(quitMessage));
    request_buffer.push(quitData);
  }

  for(int i = 0; i < w; i++) {
    workerThread.at(i).join();
  }

  gettimeofday (&end, 0);
  hc.print ();
  int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
  int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);

  cout << "Elapsed Time: " << secs << " seconds and " << usecs << " micro seconds." << endl;
  cout << "Finished." << endl;

}
