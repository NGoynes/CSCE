/****************************************
** File:  Stack221.cpp
** Project: CSCE 221 Project 1, Spring 2019
** Author: Nathan Goynes
** Date: 2/9/19
** E-mail: ngoynes@tamu.edu
**
** This file contains the function implementations of the Stack221 class
**
**
****************************************/
#ifndef STACK221_CPP
#define STACK221_CPP

#include "Stack221.h"
#include "Queue221.h"
using namespace std;

template<class T>
//Stack221
//Default constructor
Stack221<T>::Stack221() {

}

template<class T>
//Stack221
//Parameterized constructor
Stack221<T>::Stack221(T val) {
  Push(val);
}

template<class T>
//~Stack221
//Destructor
Stack221<T>::~Stack221() {
  Clear();
}

template<class T>
//Stack221
//Copy constructor
Stack221<T>::Stack221(Stack221 const& source) {
  Node221<T>* curr = source.head;
  Stack221<T> tempS;

  //push data into a temporary stack
  while (curr != nullptr) {
    tempS.Push(curr->data);
    curr = curr->next;
  }

  //push the data (that is now reversed) into stack copy
  curr = tempS.head;
  while(curr != nullptr) {
    Push(curr->data);
    curr = curr->next;
  }
}

template<class T>
//Top
//Returns item at top of stack
T Stack221<T>::Top() {
  if (this->head == nullptr) {
    throw Exceptions221("Stack - Attempt to access top of empty stack");
  }
  return this->head->data;
}

template<class T>
//Size
//Returns size of a stack
int Stack221<T>::Size() const {
  int i = 0;
  Node221<T>* curr = this->head;

  while (curr != nullptr) {
    curr = curr->next;
    i++;
  }

  return i;
}

template<class T>
//Empty
//Returns whether a stack has data or not
bool Stack221<T>::Empty() const {
  if (this->Size() != 0) {
    return 0;
  }
  else {
    return 1;
  }
}

template<class T>
//Push
//Pushes data into the stack
bool Stack221<T>::Push(T val) {
  Node221<T>* n = new Node221<T>(val);

  //error checking
  int oldSize = this->Size();
  int newSize = 0;

  //are we pushing to an empty stack
  if (this->head == nullptr) {
    this->tail = n;
  }

  n->next = this->head;
  this->head = n;

  //ensure we don't index out of bounds when pushing to empty stack
  if (n->next != nullptr) {
    n->next->prev = this->head;
  }

  //ensure we added exactly one element
  newSize = this->Size();
  if (newSize != oldSize + 1) {
    return 0;
  }
  else {
    return 1;
  }
}

template<class T>
//Pop
//Pops data from the stack
bool Stack221<T>::Pop() {
  Node221<T>* curr = this->head;

  //are we trying to pop an empty stack? (error)
  if (curr == nullptr) {
    return 0;
	}

  //check bounds of the list and edit head and tail pointers accordingly, ensuring we never index out of the list
  //popping from a list with one item
	if (curr->next == nullptr && curr->prev == nullptr) {
		this->head = nullptr;
    this->tail = nullptr;
	}
  //standard pop
	else {
		this->head = curr->next;
		curr->next->prev = nullptr;
		curr->next = nullptr;
	}

	delete(curr);
  return 1;
}

template<class T>
//Clear
//Clears a stack
bool Stack221<T>::Clear() {
  Node221<T>* curr = this->head;

  //iterate through the list and pop all the data
  while (curr != nullptr) {
    curr = curr->next;
    Pop();
  }

  //just for good measure
  delete(curr);

  //error checking
  if (this->Size() != 0) {
    return 0;
  }
  else {
    return 1;
  }
}

#endif
