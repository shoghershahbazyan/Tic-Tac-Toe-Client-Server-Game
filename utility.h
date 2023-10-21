#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
	
	void recvData(int, char*, size_t);
	bool checkReadyStatus(const int, const int);



#endif // UTILITY_H
