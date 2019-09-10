/****************************************
** File:  TicTacTrie.h
** Project: CSCE 221 Project 2, Spring 2019
** Author: Nathan Goynes
** Date: 3/13/19
** E-mail: ngoynes@tamu.edu
**
** This file is header file of the TicTacTrie class.
** This class will contain the trie data structure that will hold
** all paths for the TicTacToe games and keeps track of wins, draws,
** and the size.
**
****************************************/

#ifndef TICTACTRIE_H
#define TICTACTRIE_H
#include "TicTacToe.h"

class TicTacTrie : public TicTacToe {
public:

  /**********************************************************************
   * Name: addGame
   * PreCondition: A game of TicTacToe to be inserted into a trie
   *
   * PostCondition: Creates a trie representing many games of TicTacToe
   *********************************************************************/
  void addGame(TicTacToe);

  TicTacNode* getRoot() { return trieRoot; }

  int getXWins() { return m_xWins; }

  int getOWins() { return m_oWins; }

  int getDraws() { return m_draws; }

  int getSize() { return m_size; }

private:

  TicTacNode* trieRoot = nullptr;

  int m_xWins = 0;

  int m_oWins = 0;

  int m_draws = 0;

  int m_size = 0;

};

#endif
