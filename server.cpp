//#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
//#include <sys/socket.h>
//#include <netinet/in.h>

#include "utility.h"

class Player
{
	private:
		bool ready;
		std::string name;
	public:
		Player(std::string& str) : ready{false}, name{str} {} 
		void setReady(){ ready = true; }
		bool getStatus() { return ready;}
};
/*
class Client
{
	private:
		int sockNum;
		struct sockAddr;	
	public:
		
};
*/

int main() {
    int serverSocket, clientSocket1, clientSocket2;
    int port = 12345; // Port number to listen on
    
    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket" << std::endl;
        exit(1);
    }

    // Configure the server address structure
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the server socket to the IP and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 2) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        exit(1);
    }

    std::cout << "Server listening on port " << port << std::endl;

    // Accept two client connections
    clientSocket1 = accept(serverSocket, NULL, NULL);
    clientSocket2 = accept(serverSocket, NULL, NULL);
	

	std::cout << "Two clients connected." << std::endl;
	char buffer[1024]; 
	bool startGame{false}, startGame1{false}, startGame2{false};
	
	// Send a game request to clients
	send(clientSocket1, "Game request: Are you ready to play? (Type 'yes' or 'no')", 100, 0);
	send(clientSocket2, "Game request: Are you ready to play? (Type 'yes' or 'no')", 100, 0);

	// Receive responses from clients
	memset(buffer, 0, sizeof(buffer));
	
	//recv(clientSocket1, buffer, sizeof(buffer), 0);
	recvData(clientSocket1, buffer, sizeof(buffer));
	checkReadyStatus();
	std::cout << "Client 1 response: " << buffer << std::endl;
	startGame1 = strcmp("yes", buffer) == 0;
	std::cout << "Player 1 is ready: " << startGame1 << std::endl;

	memset(buffer, 0, sizeof(buffer));
	recv(clientSocket2, buffer, sizeof(buffer), 0);
	std::cout << "Client 2 response: " << buffer << std::endl;
	startGame2 = strcmp("yes", buffer) == 0;
	std::cout << "Player 2 is ready: " << startGame2 << std::endl;


	startGame = startGame1 & startGame2;
	
	memset(buffer, 0, sizeof(buffer));
	startGame ? strcpy(buffer, "Players are ready to start the game :)") : strcpy(buffer, "Players are not ready to start the game (:");
	send(clientSocket1, buffer, sizeof(buffer), 0);
	send(clientSocket2, buffer, sizeof(buffer), 0); 
	std::cout << buffer << std::endl;

    while (false) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket1, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cerr << "Client 1 disconnected" << std::endl;
            break;
        }
        
	std::cout << "Client 1: " << buffer << std::endl;
        send(clientSocket1, buffer, bytesReceived, 0);
	
	if (std::string(buffer) == "exit") break;

        memset(buffer, 0, sizeof(buffer));
        bytesReceived = recv(clientSocket2, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cerr << "Client 2 disconnected" << std::endl;
            break;
        }
        std::cout << "Client 2: " << buffer << std::endl;
        send(clientSocket2, buffer, bytesReceived, 0);
	
	if (std::string(buffer) == "exit") break;

    }

    // Close the sockets
    close(clientSocket1);
    close(clientSocket2);
    close(serverSocket);

    return 0;
}

