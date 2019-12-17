#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <algorithm>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

//ps -aux | awk '/init/{print $1}' | sort -r
//awk '{print $1 $11}' < test.txt | head -10 | head -8 | head -7 | sort > output.txt

string trim (string input) {
  int i=0;
  while (i < input.size() && input [i] == ' ')
    i++;
  if (i < input.size())
    input = input.substr (i);
  else{
    return "";
  }

  i = input.size() - 1;
  while (i>=0 && input[i] == ' ')
    i--;
  if (i >= 0)
    input = input.substr (0, i+1);
  else
    return "";

  return input;
}

vector<string> split (string line, string separator=" ") {
  vector<string> result;
  size_t found = line.find(separator);
  int quoteCount = 0;
  while (line.size()) {
    quoteCount = 0;
    if (found == string::npos){
      string lastpart = trim (line);
      if (lastpart.size()>0){
        result.push_back(lastpart);
      }
      break;
    }
    for (int i = 0; i < found; ++i) {
      if (line.at(i) == '\'' || line.at(i) == '\"') {
        quoteCount++;
      }
    }
    //if we found a pair of quotes then delete them
    if (quoteCount % 2 == 0) {
      string segment = trim (line.substr(0, found));
      line = line.substr (found+1);
      if (segment.size() != 0) {
        result.push_back (segment);
      }
      found = line.find(separator);
    }
    else {
      found = line.find(separator, found + 1);
    }
  }
  return result;
}

int cd(char* path) {
  return chdir(path);
}

char** vec_to_char_array (vector<string> parts) {
  char ** result = new char * [parts.size() + 1]; // add 1 for the NULL at the end
  for (int i=0; i<parts.size(); i++){
    // allocate a big enough string
    result [i] = new char [parts [i].size() + 1]; // add 1 for the NULL byte
    strcpy (result [i], parts[i].c_str());
  }
  result [parts.size()] = NULL;
  return result;
}

void execute (string command) {
  vector<string> argstrings = split (command, " "); // split the command into space-separated parts
  vector<string> commands;
  const char* file = "";
  bool fileOut = false;
  bool fileIn = false;
  int quoteCount = 0;

  //count the quotes again
  for(int i = 0;i<argstrings.size();i++) {
    if(argstrings.at(i).find('\'') != string::npos || argstrings.at(i).find('\"') != string::npos) {
      for(int j = 0; j < argstrings.at(i).size(); ++j) {
        if(argstrings.at(i).at(j) == '\'' || argstrings.at(i).at(j) == '"') {
          quoteCount++;
        }
      }
    }
    //lets get the location of file input and output redirection if they exist and get the filenames
    if ((quoteCount % 2 == 0) && (argstrings.at(i) == "<")) {
      fileIn = true;
      file = argstrings.at(i+1).c_str();
    }
    if ((quoteCount % 2 == 0) && (argstrings.at(i) == ">")) {
      fileOut = true;
      file = argstrings.at(i+1).c_str();
    }
  }

  //if we've found a pair of quotes then delete them
  for(int i = 0; i < argstrings.size(); ++i) {
    if(argstrings.at(i).find("'") != string::npos) {
      argstrings.at(i).erase(
        remove(argstrings.at(i).begin(), argstrings.at(i).end(), '\''),
        argstrings.at(i).end()
      );
    }
    else if(argstrings.at(i).find("\"") != string::npos) {
      argstrings.at(i).erase(
        remove(argstrings.at(i).begin(), argstrings.at(i).end(),'\"'),
        argstrings.at(i).end()
      );
    }
  }

  //execute the cd command if it is present
  if (argstrings.at(0) == "cd") {
    vector<string> cdVal;
    for (int i = 1; i < argstrings.size(); ++i) {
      if (argstrings.at(i) == "-") {
        cdVal.push_back("..");
        break;
      }
      cdVal.push_back(argstrings.at(i));
    }
    char** args = vec_to_char_array (cdVal);
    cd(args[0]);
  }

  //perform actual commands with file input or output
  if(fileIn || fileOut) {
    if (fileIn) {
      int fd = open(file, O_RDONLY, 0777);
      dup2(fd, 0);
    }
    if (fileOut) {
      int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
      dup2(fd, 1);
    }
    for (int i = 0; i < argstrings.size(); ++i) {
      if (argstrings.at(i) == ">" || argstrings.at(i) == "<") {
        break;
      }
      commands.push_back(argstrings.at(i));
    }
    char** args = vec_to_char_array(commands);
    execvp(args[0], args);
  }

  else {
    char** args = vec_to_char_array (argstrings);// convert vec<string> into an array of char*
    execvp (args[0], args);
  }
}

int main () {

  while (true){ // repeat this loop until the user presses Ctrl + C
    string commandline = "";/*get from STDIN, e.g., "ls  -la |   grep Jul  | grep . | grep .cpp" */
    // split the command by the "|", which tells you the pipe levels
    getline(cin, commandline);
    vector<string> tparts;
    tparts = split (commandline, "|");
    dup2(0,3);
    // for each pipe, do the following:
    for (int i=0; i<tparts.size(); i++) {
      // make pipe
      int fd[2];
      pipe(fd);
      if (!fork()) {
        // redirect output to the next level
        // unless this is the last level
        if (i < tparts.size() - 1) {
          // redirect STDOUT to fd[1], so that it can write to the other side
          dup2 (fd[1], 1);
          close (fd[1]);   // STDOUT already points fd[1], which can be closed
        }
        //execute function that can split the command by spaces to
        // find out all the arguments, see the definition
        execute (tparts [i]); // this is where you execute
      }
      else {
        wait(0);            // wait for the child process
        // then do other redirects
        dup2 (fd[0], 0);
        close (fd[1]);
      }
    }

    dup2(3,0);

  }
}
