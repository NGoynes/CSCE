/****************************************
** File:  TicTacToe.h
** Project: CSCE 221 Project 2, Spring 2019
** Author: Nathan Goynes
** Date: 3/13/19
** E-mail: ngoynes@tamu.edu
**
** This file is header file of the TicTacTrie class.
** This class is essentially a linked list of TicTacNodes
** that contains the information about the individual game
** we just read in.
**
****************************************/

#ifndef TICTACTOE_H
#define TICTACTOE_H
#include "TicTacNode.h"

class TicTacToe : public TicTacNode {
public:

  /**********************************************************************
   * Name: TicTacToe (Constructor)
   * PreCondition: None
   *
   * PostCondition: a game of tictactoe with variables initialized
   * to 0, 1, or nullptr
   *********************************************************************/
  TicTacToe();

  /**********************************************************************
   * Name: checkWin
   * PreCondition: A player character and TicTacNode passed to check for
   * a win
   *
   * PostCondition: If a win is detected then output 1, 0 otherwise
   *********************************************************************/
  bool checkWin(char, const TicTacNode&);

  /**********************************************************************
   * Name: readGame
   * PreCondition: A file string containing a game of tictactoe passed
   * to be made into a linked list
   *
   * PostCondition: Creates a linked list representing a game of tictactoe
   *********************************************************************/
  void readGame(const std::string&);

  bool getIsOver() { return m_isOver; }

  int getSize() { return m_size; }

  int getResults() { return m_results; }

  TicTacNode* root;

private:

  int m_size;

  bool m_isOver;

  int m_results;

};

#endif
