/****************************************
** File:  TicTacNode.cpp
** Project: CSCE 221 Project 2, Spring 2019
** Author: Nathan Goynes
** Date: 3/13/19
** E-mail: ngoynes@tamu.edu
**
** This file contains the function implementations of the TicTacNode class
**
**
****************************************/

#include <sstream>
#include "TicTacNode.h"
using namespace std;

//TicTacNode()
//Default constructor
TicTacNode::TicTacNode() {
  for (int i = 0; i < 9; ++i) {
    //give empty node a blank board and vector of nullptrs
    m_children.push_back(nullptr);
    m_board.insert(pair<int, char>(i, '-'));
  }
}

//operator=
//overloaded operator= for TicTacNode
TicTacNode& TicTacNode::operator=(const TicTacNode& source) {
  //assign lhs with rhs elements
  for (unsigned int i = 0; i < source.m_board.size(); ++i) {
    this->m_board.insert(pair<int,char>(i, source.m_board.at(i)));
  }

  //give lhs rhs' vector of children
  this->m_children = source.m_children;

  return *this;
}

//operator==
//overloaded operator== for TicTacNode
bool TicTacNode::operator==(const TicTacNode& rhs) {
  //if the sizes aren't equal then return 0 immediately
  if (this->m_board.size() != rhs.m_board.size()) {
    return 0;
  }

  //else compare each value
  for (unsigned int i = 0; i < this->m_board.size(); ++i) {
    if (this->m_board.at(i) != rhs.m_board.at(i)) {
      return 0;
    }
  }

  //else we return 1
  return 1;
}

//print
//helper function for overloaded operator<<
string TicTacNode::print() const {
  stringstream outputString;
  for (unsigned int i = 0; i < this->m_board.size(); ++i) {
    outputString << this->m_board.at(i);
    if ((i == 2) || (i == 5) || (i == 8)) {
      outputString << '\n';
    }
  }
  return outputString.str();
}

//operator<<
//overloaded operator<< for TicTacNode
ostream& operator<<(ostream& os, const TicTacNode& ttn) {
  os << ttn.print();
  return os;
}
