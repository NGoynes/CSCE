/****************************************
** File:  Stack221.h
** Project: CSCE 221 Project 1, Spring 2019
** Author: Nathan Goynes
** Date: 2/9/19
** E-mail: ngoynes@tamu.edu
**
** This file is header file of the Stack221 class.
** It generates a linked list resembling that of the STL Stack.
**
****************************************/

#ifndef STACK221_H
#define STACK221_H
#include "List221.h"

template<class T>
struct Stack221 : public List221<T> {
  /**********************************************************************
   * Name: Stack221 (Constructor)
   * PreCondition: None
   *
   * PostCondition: Empty Stack
   *********************************************************************/
  Stack221();

  /**********************************************************************
   * Name: Stack221 (Parameterized Constructor)
   * PreCondition: None
   *
   * PostCondition: Stack with one node of data
   *********************************************************************/
  Stack221(T);

  /**********************************************************************
   * Name: ~Stack221 (Destructor)
   * PreCondition: Stack with data
   *
   * PostCondition: Destruction of Stack
   *********************************************************************/
  ~Stack221();

  /**********************************************************************
   * Name: Stack221 (Copy Constructor)
   * PreCondition: Passed a Stack containing some data
   *
   * PostCondition: Deep copy of passed Stack
   *********************************************************************/
  Stack221(Stack221 const&);

  /**********************************************************************
   * Name: Top
   * PreCondition: Called by Stack with some data
   *
   * PostCondition: Returns the item at the top of the Stack
   *********************************************************************/
  T Top();

  /**********************************************************************
   * Name: Size
   * PreCondition: Called by Stack with or without data
   *
   * PostCondition: Returns size as an integer of the Stack
   *********************************************************************/
  int Size() const;

  /**********************************************************************
   * Name: Empty
   * PreCondition: Called by Stack with or without nodes
   *
   * PostCondition: Returns 1 if Stack is empty, 0 otherwise
   *********************************************************************/
  bool Empty() const;

  /**********************************************************************
   * Name: Push
   * PreCondition: Stack of matching data type
   *
   * PostCondition: Returns 1 if object was appended to the Stack, 0 otherwise
   *********************************************************************/
  bool Push(T);

  /**********************************************************************
   * Name: Pop
   * PreCondition: Stack with some amount of data
   *
   * PostCondition: Returns 1 if object was removed from Stack, 0 otherwise
   *********************************************************************/
  bool Pop();

  /**********************************************************************
   * Name: Clear
   * PreCondition: Stack object
   *
   * PostCondition:  Returns 1 if Stack was able to be cleared of data, 0 otherwise
   *********************************************************************/
  bool Clear();

};

#include "Stack221.cpp"
#endif
