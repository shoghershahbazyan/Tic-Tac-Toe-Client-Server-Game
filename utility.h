#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sstream>
	
void recvData(int, char*, size_t);
bool checkReadyStatus(const int, const int);
bool processMove(std::string&, int(&arr)[2]);


#endif // UTILITY_H
