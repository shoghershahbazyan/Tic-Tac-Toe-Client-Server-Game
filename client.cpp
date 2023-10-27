#include <string>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <condition_variable>

#include "utility.h"

void sendRecv(int client, std::vector<std::vector<char>>& board, const char player)
{
	bool gameOver{false};
	char buffer[1024];
	char winner{};
	while (!gameOver) {
		char buffeddr[1024];
		recvData(client, buffer, sizeof(buffer));
		std::cout << buffer << std::endl;
		size_t last = std::strlen(buffer);
		if (last > 0 && buffer[last -1] == ':') {
			std::string message;
			do {
				std::getline(std::cin, message);
				if (message == "exit") break;
			} while (!processMove(message, board, player));
			send(client, message.c_str(), message.size(), 0);
			if (message == "exit") break;
			gameOver = checkWin(board);
			if (gameOver) {
				winner = player;
			}
		} else {
			recvData(client, buffer, sizeof(buffer));
			char player2 = (player == 'X' ? 'O' : 'X');
			std::cout << player2 << "  made a move " << std::endl;
			std::string tmp = std::string(buffer); 
			processMove(tmp, board, player2);
			gameOver = checkWin(board);
			if (gameOver) {
				winner = player2;
			}
		}
	}
	recvData(client, buffer, sizeof(buffer));
	std::cout << buffer << std::endl;
	if (winner == player) {
		std::cout << "Congrads you won" << std::endl;
	} else {
		std::cout << "You lose" << std::endl;
	}
	std::cout << "\n___________GAME OVER_________" << std::endl;
}

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

