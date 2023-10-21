#include <string>
#include <cstdlib>
#include <unistd.h>

#include "utility.h"
#include "game.h"
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
	bool startGame = checkReadyStatus(clientSocket1, clientSocket2);

    while (startGame) {
	TicTacToe game;
	int row, col;
	bool gameWon{false};
		while (true) {
			std::string board = game.displayBoard();
			send(clientSocket1, board.c_str(), sizeof(board), 0);
			send(clientSocket2, board.c_str(), sizeof(board), 0);
			std::cout << board << std::endl;
			break;
		}
		break;    
	}

    // Close the sockets
    close(clientSocket1);
    close(clientSocket2);
    close(serverSocket);

    return 0;
}

