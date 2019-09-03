/****************************************
** File:  Queue221.cpp
** Project: CSCE 221 Project 1, Spring 2019
** Author: Nathan Goynes
** Date: 2/9/19
** E-mail: ngoynes@tamu.edu
**
** This file contains the function implementations of the Queue221 class
**
**
****************************************/
#ifndef QUEUE221_CPP
#define QUEUE221_CPP

#include "Queue221.h"
#include "Stack221.h"
using namespace std;

template<class T>
//Queue221
//Default constructor
Queue221<T>::Queue221() {

}

template<class T>
//Queue221
//Parameterized constructor
Queue221<T>::Queue221(T val) {
  Push(val);
}

template<class T>
//~Queue221
//Destructor
Queue221<T>::~Queue221() {
  Clear();
}

template<class T>
//Queue221
//Copy constructor
Queue221<T>::Queue221(Queue221 const& source) {
  Node221<T>* curr = source.head;

  //copy data to new queue through standard iteration
  while(curr != nullptr) {
    Push(curr->data);
    curr = curr->next;
  }
}

template<class T>
//Front
//Returns item at the front of Queue
T Queue221<T>::Front() {
  if (this->head == nullptr) {
    throw Exceptions221("Queue - Attempt to access front of empty queue");
  }
  else {
    return this->head->data;
  }
}

template<class T>
//Back
//Returns item at the back of Queue
T Queue221<T>::Back() {
  if (this->tail == nullptr) {
    throw Exceptions221("Queue - Attempt to access back of empty queue");
  }
  else {
    return this->tail->data;
  }
}

template<class T>
//Size
//Returns size of a Queue
int Queue221<T>::Size() const {
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
//Returns whether a Queue has data or not
bool Queue221<T>::Empty() const {
  if (this->Size() != 0) {
    return 0;
  }
  else {
    return 1;
  }
}

template<class T>
//Push
//Pushes data into the Queue
bool Queue221<T>::Push(T val) {
  Node221<T>* n = new Node221<T>(val);

  //error checking
  int oldSize = this->Size();
  int newSize = 0;

  //empty list push
	if (this->tail == nullptr) {
		this->head = n;
  }

  //standard push
	n->prev = this->tail;
  this->tail = n;

  //ensuring we don't index out of range when we push to front
	if (n->prev != nullptr) {
		n->prev->next = this->tail;
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
//Pops data from the Queue
bool Queue221<T>::Pop() {
  Node221<T>* curr = this->head;

  //are we trying to pop an empty queue? (error)
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
//Clears a Queue
bool Queue221<T>::Clear() {
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
