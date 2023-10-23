#include <string>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#include "utility.h"
#include "game.h"
int main() {
    int clientSocket;
    int port = 12345; // Port number to connect to
    char buffer[1024];

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating client socket" << std::endl;
        exit(1);
    }

    // Configure the server address structure
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to the server" << std::endl;
        exit(1);
    }

	// Receive and display the game request
	recvData(clientSocket, buffer, sizeof(buffer));
	std::cout << "Server: " << buffer << std::endl;

	// Get the client's response
	std::string response;
	std::cout << "Your response: ";
	std::getline(std::cin >> std::ws, response);
	send(clientSocket, response.c_str(), response.size(), 0);
	
	recvData(clientSocket, buffer, sizeof(buffer));
	std::cout << buffer << std::endl;


    //while (true) {
        std::cout << "Let's play Tic-Tac-Toe!" << std::endl;
	// Create the instance of the game class
	TicTacToe game;
	
	// Set the name of the player
	char playerName{};
	recvData(clientSocket, buffer, 1);
	playerName = buffer[0];
	std::string startMove = "Player " + std::string(1, playerName) +  ", enter your move (row and column): ";
	bool makeMove = playerName == 'X' ? true : false;
	// Sart the game
	while (true) {
		recvData(clientSocket, buffer, sizeof(buffer));
		std::cout << buffer << std::endl;
		std::cout << startMove << std::endl;		
		
		std::string message;
		std::getline(std::cin, message);

		send(clientSocket, message.c_str(), message.size(), 0);

/*
		if (message == "exit") break;

		memset(buffer, 0, sizeof(buffer));
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived <= 0) {
		    std::cerr << "Server disconnected" << std::endl;
		    break;
		}
		std::cout << "Server: " << buffer << std::endl;
	   
		if (std::string(buffer) == "exit") break;
		*/
	}
	//break;
 //}

    // Close the socket
    close(clientSocket);
}

