#include "utility.h"

void recvData(int socket, char* buffer, size_t size) {
	int bytesReceived = recv(socket, buffer, size, 0);
	if (bytesReceived <= 0) {
		std::cerr << "Disconnected" << std::endl;
		exit(0);
	}
}

bool checkReadyStatus(){
	return true;
}
