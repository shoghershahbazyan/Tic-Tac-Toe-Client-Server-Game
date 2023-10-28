#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <cstdlib>

#include "game.h"

	
void recvData(int, char*, size_t);	// Receive data from a socket and handle potential errors.
bool checkReadyStatus(const int, const int);	// Check if both players are ready to start the game.
bool toInt(const std::string&, int&, int&);	// Convert a string input to two integer values.
bool processMove(const std::string&, std::vector<std::vector<char>>&, const char);	// Process a player's move on the game board, returning true if it's valid.
bool checkWin(const std::vector<std::vector<char>>&);	// Check if there's a win condition on the game board, returning true if there's a winner.
void sendData(const int clientSocket1, const int clientSocket2, char player1, char player2, std::string& board);	// Method to send data to palyer
void play(int clientSocket1, int clientSocket2, TicTacToe& game);	// Method to pay a game
void sendRecv(int client, std::vector<std::vector<char>>& board, const char player);	// Method to run the game for client

#endif // UTILITY_H
