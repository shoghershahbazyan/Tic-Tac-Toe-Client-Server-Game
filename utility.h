#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
	
	void recvData(int, char*, size_t);
	bool checkReadyStatus();



#endif // UTILITY_H
