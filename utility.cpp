#include "utility.h"

void recvData(int socket, char* buffer, size_t size) {
	memset(buffer, 0, size);
	int bytesReceived = recv(socket, buffer, size, 0);
	if (bytesReceived <= 0) {
		std::cerr << "Disconnected" << std::endl;
		exit(0);
	}
}

bool checkReadyStatus(const int clientSocket1, const int clientSocket2){
	char buffer[1024]; 
	bool startGame{false}, startGame1{false}, startGame2{false};
	
	// Send a game request to clients
	send(clientSocket1, "Game request: Are you ready to play? (Type 'yes' or 'no')", 100, 0);
	send(clientSocket2, "Game request: Are you ready to play? (Type 'yes' or 'no')", 100, 0);

	// Receive responses from clients
	recvData(clientSocket1, buffer, sizeof(buffer));
	std::cout << "Client 1 response: " << buffer << std::endl;
	startGame1 = strcmp("yes", buffer) == 0;

	recvData(clientSocket2, buffer, sizeof(buffer));
	std::cout << "Client 2 response: " << buffer << std::endl;
	startGame2 = strcmp("yes", buffer) == 0;
	startGame = startGame1 & startGame2;
	
	memset(buffer, 0, sizeof(buffer));
	startGame ? strcpy(buffer, "Players are ready to start the game :)") : strcpy(buffer, "Players are not ready to start the game (:");
	send(clientSocket1, buffer, sizeof(buffer), 0);
	send(clientSocket2, buffer, sizeof(buffer), 0); 
	std::cout << buffer << std::endl;

	return startGame;
}

bool  processMove(std::string& input, int(& arr)[2])
{
	std::istringstream iss(input);
	if (iss >> arr[0] >> arr[1]) {
		return true;	
	}
	return false;
}
