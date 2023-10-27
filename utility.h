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

	
void recvData(int, char*, size_t);
bool checkReadyStatus(const int, const int);
bool toInt(const std::string&, int&, int&);
bool processMove(const std::string&, std::vector<std::vector<char>>&, const char); 
bool checkWin(const std::vector<std::vector<char>>&);
// Method to send data to palyer
void sendData(const int clientSocket1, const int clientSocket2, char player1, char player2, std::string& board);
// Method to pay a game
void play(int clientSocket1, int clientSocket2, TicTacToe& game);

// Method to run the game for client

void sendRecv(int client, std::vector<std::vector<char>>& board, const char player);

#endif // UTILITY_H
