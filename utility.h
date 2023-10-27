#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sstream>
#include <vector>
	
void recvData(int, char*, size_t);
bool checkReadyStatus(const int, const int);
bool toInt(const std::string&, int&, int&);
bool processMove(const std::string&, std::vector<std::vector<char>>&); 

#endif // UTILITY_H
