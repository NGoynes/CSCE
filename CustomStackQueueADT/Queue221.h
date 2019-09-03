/****************************************
** File:  Queue221.h
** Project: CSCE 221 Project 1, Spring 2019
** Author: Nathan Goynes
** Date: 2/9/19
** E-mail: ngoynes@tamu.edu
**
** This file is header file of the Queue221 class.
** It generates a linked list resembling that of the STL Queue.
**
****************************************/

#ifndef QUEUE221_H
#define QUEUE221_H
#include "List221.h"

template<class T>
struct Queue221 : public List221<T> {

  /**********************************************************************
   * Name: Queue221 (Constructor)
   * PreCondition: None
   *
   * PostCondition: Empty queue
   *********************************************************************/
  Queue221();

  /**********************************************************************
   * Name: Queue221 (Parameterized Constructor)
   * PreCondition: None
   *
   * PostCondition: Queue with one node of data
   *********************************************************************/
  Queue221(T);

  /**********************************************************************
   * Name: ~Queue221 (Destructor)
   * PreCondition: Queue with data
   *
   * PostCondition: Destruction of queue
   *********************************************************************/
  ~Queue221();

  /**********************************************************************
   * Name: Queue221 (Copy Constructor)
   * PreCondition: Passed a queue containing some data
   *
   * PostCondition: Deep copy of passed queue
   *********************************************************************/
  Queue221(Queue221 const&);

  /**********************************************************************
   * Name: Front
   * PreCondition: Called by Queue with some data
   *
   * PostCondition: Returns the item at the front of the queue
   *********************************************************************/
  T Front();

  /**********************************************************************
   * Name: Back
   * PreCondition: Called by Queue with some data
   *
   * PostCondition: Returns the item at the back of the queue
   *********************************************************************/
  T Back();

  /**********************************************************************
   * Name: Size
   * PreCondition: Called by queue with or without data
   *
   * PostCondition: Returns size as an integer of the queue
   *********************************************************************/
  int Size() const;

  /**********************************************************************
   * Name: Empty
   * PreCondition: Called by queue with or without nodes
   *
   * PostCondition: Returns 1 if queue is empty, 0 otherwise
   *********************************************************************/
  bool Empty() const;

  /**********************************************************************
   * Name: Push
   * PreCondition: Queue of matching data type
   *
   * PostCondition: Returns 1 if object was appended to the queue, 0 otherwise
   *********************************************************************/
  bool Push(T);

  /**********************************************************************
   * Name: Pop
   * PreCondition: Queue with some amount of data
   *
   * PostCondition: Returns 1 if object was removed from queue, 0 otherwise
   *********************************************************************/
  bool Pop();

  /**********************************************************************
   * Name: Clear
   * PreCondition: Queue object
   *
   * PostCondition:  Returns 1 if queue was able to be cleared of data, 0 otherwise
   *********************************************************************/
  bool Clear();

};

#include "Queue221.cpp"
#endif
