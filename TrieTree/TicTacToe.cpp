/****************************************
** File:  TicTacToe.cpp
** Project: CSCE 221 Project 2, Spring 2019
** Author: Nathan Goynes
** Date: 3/13/19
** E-mail: ngoynes@tamu.edu
**
** This file contains the function implementations of the TicTacToe class
**
**
****************************************/

#include "TicTacToe.h"
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


//TicTacToe()
//Default Constructor
TicTacToe::TicTacToe() {
  m_isOver = false;
  m_size = 0;
  m_results = 1;
  root = nullptr;
  this->m_children.push_back(nullptr);
}

//checkWin
//Determines if given player has won a game of tictactoe
bool TicTacToe::checkWin(char player, const TicTacNode& board) {
  if ((player == board.m_board.at(0)) && (player == board.m_board.at(1)) && (player == board.m_board.at(2))) {
    return 1;
  }
  else if ((player == board.m_board.at(3)) && (player == board.m_board.at(4)) && (player == board.m_board.at(5))) {
    return 1;
  }
  else if ((player == board.m_board.at(6)) && (player == board.m_board.at(7)) && (player == board.m_board.at(8))) {
    return 1;
  }
  else if ((player == board.m_board.at(0)) && (player == board.m_board.at(3)) && (player == board.m_board.at(6))) {
    return 1;
  }
  else if ((player == board.m_board.at(1)) && (player == board.m_board.at(4)) && (player == board.m_board.at(7))) {
    return 1;
  }
  else if ((player == board.m_board.at(2)) && (player == board.m_board.at(5)) && (player == board.m_board.at(8))) {
    return 1;
  }
  else if ((player == board.m_board.at(0)) && (player == board.m_board.at(4)) && (player == board.m_board.at(8))) {
    return 1;
  }
  else if ((player == board.m_board.at(2)) && (player == board.m_board.at(4)) && (player == board.m_board.at(6))) {
    return 1;
  }
  else {
    return 0;
  }
}

//readGame
//creates a linked last from a file of tictactoe
void TicTacToe::readGame(const string& game) {
  ifstream file;
  file.open(game, ios_base::in);
  if(file.fail()) {
    cout << "Game was not successfully opened." << endl;
    exit(1);
  }

  vector<char> temp;
  vector<char> last;
  string line;
  this->m_size = 0;
  while(getline(file, line)) {
    TicTacNode* curr = this->root;
    TicTacNode* node = new TicTacNode();
    if (line.size() != 0) {
      if (temp.size() < 9) {
        for (int i = 0; i < 3; ++i) {
          //push board to a temporary vector
          temp.push_back(line.at(i));
        }
      }
      //are we starting a new board?
      if (temp.size() == 9) {
        //make a tictacnode out of our vector
        for (unsigned int i = 0; i < temp.size(); ++i) {
          node->m_board.at(i) = temp.at(i);
        }
        //increment size of tictactoe game
        this->m_size++;
        //empty vector but save the last node for end game check
        last = temp;
        temp.clear();
        //link TicTacNodes
        //insertion in empty list
        if (curr == nullptr) {
          node->m_children.at(0) = root;
          root = node;
        }
        //plain insertion at end of list
        else {
          //find prev
          while (curr->m_children.at(0) != nullptr) {
            curr = curr->m_children.at(0);
          }
          //assign prev's children to current node
          curr->m_children.at(0) = node;
        }
      }
    }
  }
  //find last node
  TicTacNode* curr = root;
  while (curr->m_children.at(0) != nullptr) {
    curr = curr->m_children.at(0);
  }
  //check wins, draws, !end
  //check if game didn't end first
  int xCount = 0;
  int oCount = 0;
  xCount = count(last.begin(), last.end(), 'X');
  oCount = count(last.begin(), last.end(), 'O');
  if ((xCount < 3) && (oCount < 3)) {
    m_results = 0;
    m_isOver = 0;
  }
  else {
    m_isOver = 1;
  }

  //call our checkWin function with both players and the last node we linked
  if (m_isOver == 1) {
    bool xWin = 0;
    bool oWin = 0;
    xWin = checkWin('X', *curr);
    oWin = checkWin('O', *curr);
    if ((xWin == 1) && (oWin == 0)) {
      m_results = 1;
    }
    else if ((oWin == 1) && (xWin == 0)) {
      m_results = 2;
    }
    else {
      m_results = 3;
    }
  }

}
