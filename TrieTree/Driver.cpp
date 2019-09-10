/**************************************************************
 * File:    Driver.cpp
 * Project: CSCE 221 - Project 2
 * Author : Nathan Goynes
 * Date   : 2/13/19
 * Section: 519
 * E-mail:  ngoynes@tamu.edu
 *
 * Sample driver file for project 2.
 *
 *************************************************************/

 #include <fstream>
 #include "TicTacNode.h"
 #include "TicTacToe.h"
 #include "TicTacTrie.h"

 using namespace std;

 int main(int argc, char** argv) {
   if (argc < 2) {
     cout << "Usage: " << argv[0] << " games_file" << endl;
     return 1;
   }
   else {
     //get the game file
     string game;
     game = argv[1];

     //open file
     ifstream file;
     file.open(game, ios_base::in);
     if(file.fail()) {
       cout << "Game was not successfully opened." << endl;
       exit(1);
     }

     //make games and thus a trie out of the games
     TicTacTrie* trie = new TicTacTrie;
     string line;
     while(!file.eof()) {
       getline(file, line);
       TicTacToe* game = new TicTacToe;
       game->readGame(line);
       trie->addGame(*game);

       //run output
       cout << "======================" << endl;
       cout << "Reading: " << line << endl;
       cout << "======================" << endl;
       TicTacNode* curr = new TicTacNode;
       curr = game->root;
       while(curr->m_children.at(0) != nullptr) {
         curr = curr->m_children.at(0);
       }

       //output game and results
       int results = 0;
       results = game->getResults();
       if (results == 0) {
         //game did not end
         cout << "The game did not end." << endl;
       }
       if (results == 1) {
         //Player X won
         cout << "Player X wins!" << endl;
       }
       if (results == 2) {
         //Player O won
         cout << "Player O wins!" << endl;
       }
       if (results == 3) {
         //Game ended in a draw
         cout << "The game was a draw!" << endl;
       }
       cout << "Game Board: " << endl;
       cout << *curr << endl;
     }
     int xWins = 0;
     int oWins = 0;
     int draws = 0;
     int size = 0;
     xWins = trie->getXWins();
     oWins = trie->getOWins();
     draws = trie->getDraws();
     size = trie->getSize();
     cout << "Final Trie Statistics" << endl;
     cout << "=====================" << endl;
     cout << "Player X Wins: \t" << xWins << endl;
     cout << "Player O Wins: \t" << oWins << endl;
     cout << "Draws: \t\t" << draws << endl;
     cout << "Trie Size: \t" << size;
   }
   return 0;
 }
