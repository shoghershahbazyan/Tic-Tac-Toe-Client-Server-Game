#include <string>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "utility.h"
#include "game.h"

void play(int clientSocket1, int clientSocket2, TicTacToe& game)
{
	bool flag = true;
	bool gameOver{false};
	char winner{'a'};
	while (!gameOver) {
		std::string board = game.displayBoard();
		std::cout << board << std::endl;
		char buffer[1024];
		int row{}, col{};
		if (flag) {
			flag = false;
			std::string boardX = board + "\nServer: Player X make move:";
			std::string boardO = board + "\nServer: Player O please whait...";
			send(clientSocket1, boardX.c_str(), boardX.size(), 0);
			send(clientSocket2, boardO.c_str(), boardO.size(), 0);
			recvData(clientSocket1, buffer, sizeof(buffer));
			std::cout << "Player X: " << buffer << std::endl;
			toInt(std::string(buffer), row, col);
			if (game.makeMove(row, col)) {
				if (game.checkWin()) {
					std::cout << game.displayBoard() << std::endl;
					std::cout << "Player X wins!! " << std::endl;
					gameOver = true;
					winner = 'X';
					break; // break;
				} else if (game.checkDraw()) {
					std::cout << game.displayBoard() << std::endl;
					std::cout << "It's a Draw!" << std::endl;
					gameOver = true;
					break; // winner = 'N';
				}
			}
			
			send(clientSocket2, buffer, sizeof(buffer), 0);
		} else {
			flag = true;
			std::string boardX = board + "\nServer: Player X please whait...";
			std::string boardO = board + "\nServer: Player O make a move:";
			send(clientSocket1, boardX.c_str(), boardX.size(), 0);
			send(clientSocket2, boardO.c_str(), boardO.size(), 0);
			recvData(clientSocket2, buffer, sizeof(buffer));
			toInt(std::string(buffer), row, col);
			game.makeMove(row, col);
			std::cout << "Player O: " << buffer << std::endl;
			if (game.makeMove(row, col)) {
				if (game.checkWin()) {
					std::cout << game.displayBoard() << std::endl;
					std::cout << "Player O wins!! " << std::endl;
					gameOver = true;
					break; // winner = 'O';
				} else if (game.checkDraw()) {
					std::cout << game.displayBoard() << std::endl;
					std::cout << "It's a Draw!" << std::endl;
					gameOver = true;
					break; //winner = 'N';
				}
			}
			send(clientSocket1, buffer, sizeof(buffer), 0);
		}
		// send the game status X, Y, N
		//buffer[0] = winner;
		//send(clientSocket1, buffer, 1, 0);
		//send(clientSocket2, buffer, 1, 0); 
	}
}

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

	std::cout << "Let's play Tic-Tac-Toe!" << std::endl;
	// Set the players names
	send(clientSocket1, "X", 1, 0);
	send(clientSocket2, "O", 1, 0);
	TicTacToe game;
	
	std::thread threadX(play, clientSocket1, clientSocket2, std::ref(game));
  
	threadX.join();
 

    // Close the sockets
    close(clientSocket1);
    close(clientSocket2);
    close(serverSocket);
}
