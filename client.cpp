#include <string>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <condition_variable>

#include "utility.h"

std::condition_variable cv;
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
	std::cout << "Your response: (yes/no) ";
	std::getline(std::cin >> std::ws, response);
	send(clientSocket, response.c_str(), response.size(), 0);
	recvData(clientSocket, buffer, sizeof(buffer));
	std::cout << buffer << std::endl;


    	if (response == "yes") {
  	      std::cout << "Let's play Tic-Tac-Toe!" << std::endl;
		// Set the name of the player
		char playerName{};
		recvData(clientSocket, buffer, 1);
		playerName = buffer[0];
		std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));
		cv.notify_one();
		std::thread thread1(sendRecv, clientSocket, std::ref(board), playerName);	
		thread1.join();
	}
    // Close the socket
    close(clientSocket);
}

