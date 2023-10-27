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

bool toInt(const std::string& input, int& row, int& col)
{
	std::istringstream iss(input);
	if (iss >> row >> col) {
		return true;
	}	
	std::cout << "Invalid move!" << std::endl;
	return false;
}

bool  processMove(const std::string& input, std::vector<std::vector<char>>& board, const char player)
{
	int row{}, col{};
	if (!toInt(input, row, col)) {
		return false;	
	}
	if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
	    std::cout << "Invalid move. Try again. Utility.cpp" << std::endl;
	    return false;
	}
	board[row][col] = player;
	return true;
}

bool checkWin(const std::vector<std::vector<char>>& board)
{
	// Check rows, columns, and diagonals
	for (int i = 0; i < 3; i++) {
	    if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
		return true; // Row win
	    }
	    if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
		return true; // Column win
	    }
	}
	if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
	    return true; // Diagonal win
	}
	if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
	    return true; // Diagonal win
	}
	return false;
}

void sendData(const int clientSocket1, const int clientSocket2, char player1, char player2, std::string& board)
{
	std::string board1 = board + "\nServer: Player " +  std::string(1,player1) + " make move:";
	std::string board2 = board + "\nServer: Player " + std::string(1,player2) + " please whait...";
	send(clientSocket1, board1.c_str(), board1.size(), 0);
	send(clientSocket2, board2.c_str(), board2.size(), 0);
}
