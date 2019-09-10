/****************************************
** File:  TicTacTrie.cpp
** Project: CSCE 221 Project 2, Spring 2019
** Author: Nathan Goynes
** Date: 3/13/19
** E-mail: ngoynes@tamu.edu
**
** This file contains the function implementations of the TicTacTrie class
**
**
****************************************/

#include "TicTacTrie.h"
using namespace std;

//addGame
//adds game of tictactoe to a trie with all games
void TicTacTrie::addGame(TicTacToe game) {
  if (trieRoot == nullptr) {
    //set first node of game to root of trie
    trieRoot = game.root;
    cout << trieRoot->m_board.at(0);
    this->m_size = game.getSize();
  }
  else {
    //iterate through game starting with second node
    TicTacNode* add = game.root->m_children.at(0);
    TicTacNode* check = trieRoot;
    bool inTrie = 0;
    while (add != nullptr) {
      //add next move to trie
      //first check if move is already in the trie
      //check add against all the pointers in the vector
      inTrie = 0;
      for (unsigned int i = 0; i < check->m_children.size(); ++i) {
        if (inTrie == 0 && check->m_children.at(i) != nullptr) {
          if (*(add) == *(check->m_children.at(i))) {
            //if move is in the trie then move to next node and update inTrie
            add = add->m_children.at(0);
            check = check->m_children.at(0);
            inTrie = 1;
          }
        }
      }
      //are we adding a new node?
      if (inTrie == 0) {
        //use check as our prev
        for (unsigned int i = 0; i < check->m_children.size(); ++i) {
          if (check->m_children.at(i) == nullptr) {
            //add the node to the first empty spot in the vector
            check->m_children.at(i) = add;
          }
        }

        //increment size of trie for every node we add
        this->m_size++;
        //get next node
        add = add->m_children.at(0);
      }
    }
  }
  int results = game.getResults();
  if (results == 1) {
    //Player X won
    this->m_xWins++;
  }
  if (results == 2) {
    //Player O won
    this->m_oWins++;
  }
  if (results == 3) {
    //Game ended in a draw
    this->m_draws++;
  }
  return;
}
