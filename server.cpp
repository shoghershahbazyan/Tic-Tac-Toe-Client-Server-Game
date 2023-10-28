#include <string>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "utility.h"
#include "game.h"

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
	// Check if the boath players are ready to play the game
	bool startGame = checkReadyStatus(clientSocket1, clientSocket2);
	if (!startGame) {
		std::cout << "Players are not ready to paly!\n Bye" << std::endl;
		return 0;
	} else {
		std::cout << "Let's play Tic-Tac-Toe!" << std::endl;
		// Set the players names
		send(clientSocket1, "X", 1, 0);
		send(clientSocket2, "O", 1, 0);
		TicTacToe game;
	
		std::thread threadX(play, clientSocket1, clientSocket2, std::ref(game));
  
		threadX.join();
 	}

    // Close the sockets
    close(clientSocket1);
    close(clientSocket2);
    close(serverSocket);
}
