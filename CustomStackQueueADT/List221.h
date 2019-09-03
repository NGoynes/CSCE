/****************************************
** File:  List221.h
** Project: CSCE 221 Project 1, Spring 2019
** Author: Nathan Goynes
** Date: 2/9/19
** E-mail: ngoynes@tamu.edu
**
** This is the base class for our Stack and Queue classes.
** It is a pure virtual class so it will never be implemented on its own.
** Its public members are inherited by the Stack and Queue classes.
**
****************************************/

#ifndef LIST221_H
#define LIST221_H
#include "Node221.h"
#include "Exceptions221.h"

template<class T>
class List221 {
public:
  /**********************************************************************
   * Name: List221 (Constructor)
   * PreCondition: None
   *
   * PostCondition: Empty linked list
   *********************************************************************/
  List221();

  /**********************************************************************
   * Name: ~List221 (Destructor)
   * PreCondition: Linked list with data
   *
   * PostCondition: Destruction of list
   *********************************************************************/
  ~List221();

  /**********************************************************************
   * Name: List221 (Copy Constructor)
   * PreCondition: Passed a list containing some data
   *
   * PostCondition: Deep copy of passed list
   *********************************************************************/
  List221(List221 const&);

  /**********************************************************************
   * Name: Size
   * PreCondition: Called by linked list with or without data
   *
   * PostCondition: Returns size as an integer of the linked list
   *********************************************************************/
  virtual int Size() const = 0;

  /**********************************************************************
   * Name: Empty
   * PreCondition: Called by linked list with or without nodes
   *
   * PostCondition: Returns 1 if list is empty, 0 otherwise
   *********************************************************************/
  virtual bool Empty() const = 0;

  /**********************************************************************
   * Name: Push
   * PreCondition: Linked list of matching data type
   *
   * PostCondition: Returns 1 if object was appended to the list, 0 otherwise
   *********************************************************************/
  virtual bool Push(T) = 0;

  /**********************************************************************
   * Name: Pop
   * PreCondition: Linked list with some amount of data
   *
   * PostCondition: Returns 1 if object was removed from linked list, 0 otherwise
   *********************************************************************/
  virtual bool Pop() = 0;

  /**********************************************************************
   * Name: Clear
   * PreCondition: Linked list object
   *
   * PostCondition:  Returns 1 if list was able to be cleared of data, 0 otherwise
   *********************************************************************/
  virtual bool Clear() = 0;

protected:
  Node221<T>* head = nullptr;
  Node221<T>* tail = nullptr;

};

#include "List221.cpp"
#endif
