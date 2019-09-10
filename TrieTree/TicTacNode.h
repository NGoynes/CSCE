/****************************************
** File:  TicTacNode.h
** Project: CSCE 221 Project 2, Spring 2019
** Author: Nathan Goynes
** Date: 3/13/19
** E-mail: ngoynes@tamu.edu
**
** This file is header file of the TicTacTrie class.
** This class holds information about the current state of the game board.
**
****************************************/

#ifndef TICTACNODE_H
#define TICTACNODE_H
#include <map>
#include <iostream>
#include <string>
#include <vector>

struct TicTacNode {
  /**********************************************************************
   * Name: TicTacNode (Constructor)
   * PreCondition: None
   *
   * PostCondition: TicTacNode with a blank board and a vector of size
   * 9 with nullptrs
   *********************************************************************/
  TicTacNode();

  /**********************************************************************
   * Name: operator=
   * PreCondition: Passed a rhs TicTacNode containing some data
   *
   * PostCondition: Deep copy of passed TicTacNode
   *********************************************************************/
  TicTacNode& operator=(const TicTacNode&);

  /**********************************************************************
   * Name: operator==
   * PreCondition: Passed a rhs TicTacNode containing some data to be
   * compared to the lhs
   *
   * PostCondition: Output true if the two nodes are equal, false otherwise
   *********************************************************************/
  bool operator==(const TicTacNode&);

  /**********************************************************************
   * Name: print
   * PreCondition: Passed a TicTacNode containing data to be output
   * this is our helper function for the overloaded operator<<
   *
   * PostCondition: Output of the string with the board data
   *********************************************************************/
  std::string print() const;

  std::vector<TicTacNode*> m_children;

  std::map<int, char> m_board;

};

/**********************************************************************
 * Name: operator<<
 * PreCondition: Passed a rhs TicTacNode containing some data to be output
 *
 * PostCondition: Output of the board within the TicTacNode
 *********************************************************************/
std::ostream& operator<<(std::ostream& os, const TicTacNode& ttn);

#endif
