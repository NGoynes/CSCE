/**************************************************************
 * File:    Driver.cpp
 * Project: CSCE 221 - Project 1
 * Author : Nathan Goynes
 * Date   : 2/9/19
 * Section: 519
 * E-mail:  ngoynes@tamu.edu
 *
 * Sample driver file for project 1.
 *
 *************************************************************/
#include "Stack221.h"
#include "Queue221.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    Stack221<int> testStack(0);
    Stack221<string> stringStack;

    Stack221<int> *ptrStack = new Stack221<int>();

    Queue221<int> testQueue(0);
    Queue221<string> stringQueue;

    Queue221<int> *ptrQueue = new Queue221<int>();

    try {

      for (int i = 1; i <= 5; ++i) {
        testStack.Push(i);
      }

      stringStack.Push("Plate0");
      stringStack.Push("Plate1");
      stringStack.Push("Plate2");
      stringStack.Push("Plate3");
      stringStack.Push("Plate4");
      stringStack.Push("Plate5");

      Stack221<int> copyStack(testStack);

      for (int i = 1; i <= 10; ++i) {
        ptrStack->Push(i);
      }

      /*cout << "ptrStack size: " << ptrStack->Size() << endl;
      cout << "calling Clear()..." << endl;
      cout << "ptrStack Cleared? " << ptrStack->Clear() << endl;
      cout << "ptrStack size: " << ptrStack->Size() << endl << endl;

      cout << "testStack size: " << testStack.Size() << endl;
      cout << "testStack contents: " << endl;
      while (!testStack.Empty()) {
        cout << testStack.Top() << endl;
        testStack.Pop();
      }
      cout << "testStack empty? " << testStack.Empty() << endl;
      cout << endl;

      cout << "copyStack size: " << copyStack.Size() << endl;
      cout << "copyStack contents: " << endl;
      while (!copyStack.Empty()) {
        cout << copyStack.Top() << endl;
        copyStack.Pop();
      }
      cout << "copyStack empty? " << copyStack.Empty() << endl;
      cout << endl;

      cout << "stringStack size: " << stringStack.Size() << endl;
      cout << "stringStack contents: " << endl;
      while (!stringStack.Empty()) {
        cout << stringStack.Top() << endl;
        stringStack.Pop();
      }
      cout << "stringStack empty? " << stringStack.Empty() << endl;
      cout << endl;*/


      for (int i = 1; i <= 5; ++i) {
        testQueue.Push(i);
      }

      stringQueue.Push("Plate0");
      stringQueue.Push("Plate1");
      stringQueue.Push("Plate2");
      stringQueue.Push("Plate3");
      stringQueue.Push("Plate4");
      stringQueue.Push("Plate5");

      Queue221<int> copyQueue(testQueue);

      for (int i = 1; i <= 10; ++i) {
        ptrQueue->Push(i);
      }

      /*cout << "ptrQueue size: " << ptrQueue->Size() << endl;
      cout << "calling Clear()..." << endl;
      cout << "ptrQueue Cleared? " << ptrQueue->Clear() << endl;
      cout << "ptrQueue size: " << ptrQueue->Size() << endl << endl;

      cout << "testQueue size: " << testQueue.Size() << endl;
      cout << "testQueue contents: " << endl;
      while (!testQueue.Empty()) {
        cout << testQueue.Front() << endl;
        testQueue.Pop();
      }
      cout << "testQueue empty? " << testQueue.Empty() << endl;
      cout << endl;

      cout << "copyQueue size: " << copyQueue.Size() << endl;
      cout << "copyQueue contents: " << endl;
      while (!copyQueue.Empty()) {
        cout << copyQueue.Front() << endl;
        copyQueue.Pop();
      }
      cout << "copyQueue empty? " << copyQueue.Empty() << endl;
      cout << endl;

      cout << "stringQueue size: " << stringQueue.Size() << endl;
      cout << "stringQueue contents: " << endl;
      while (!stringQueue.Empty()) {
        cout << stringQueue.Front() << endl;
        stringQueue.Pop();
      }
      cout << "stringQueue empty? " << stringQueue.Empty() << endl;
      cout << endl;*/

      /*
      //let's test the exceptions
      testStack.Clear();
      testStack.Top();

      testQueue.Clear();
      testQueue.Front();
      testQueue.Back();
      */

    }
    catch (Exceptions221 &E){
        cout << "Exception: " << E.GetMessage() << endl;
    }

    delete ptrStack;
    delete ptrQueue;

    return 0;
}
