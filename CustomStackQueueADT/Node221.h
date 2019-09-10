/****************************************
** File:  Node221.h
** Project: CSCE 221 Project 1, Spring 2019
** Author: Nathan Goynes
** Date: 2/9/19
** E-mail: ngoynes@tamu.edu
**
** This is the Node221 Struct for Project 1.
** It accepts data of any type, turns it into a node, and
** assigns it next and prev pointers.
**
****************************************/

#ifndef NODE221_H
#define NODE221_H

template<class T>
struct Node221 {

  /**********************************************************************
   * Name: Node221 (Constructor)
   * PreCondition: None
   *
   * PostCondition: Empty node
   *********************************************************************/
  Node221() : data(nullptr), next(nullptr), prev(nullptr) {}

  /**********************************************************************
   * Name: Node221 (Parameterized Constructor)
   * PreCondition: None
   *
   * PostCondition: Node with data and nullptrs
   *********************************************************************/
  Node221(T data) : data(data), next(nullptr), prev(nullptr) {}

  T data;

  Node221* next;

  Node221* prev;

};

#endif
