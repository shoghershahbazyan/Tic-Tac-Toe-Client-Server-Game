#include "utility.h"

void recvData(int socket, char* buffer, size_t size) {
    // Clear the buffer by setting all its elements to 0
    memset(buffer, 0, size);

    // Receive data from the socket into the buffer
    int bytesReceived = recv(socket, buffer, size, 0);

    // Check if there was an issue with the received data
    if (bytesReceived <= 0) {
        // If no bytes were received or an error occurred, print an error message
        std::cerr << "Disconnected" << std::endl;
        
        // Exit the program (assuming this function is part of a larger program)
        exit(0);
    }
}

bool toInt(const std::string& input, int& row, int& col)
{
    // Create an input string stream to parse the input string
    std::istringstream iss(input);

    // Try to extract integers from the input stream into 'row' and 'col'
    if (iss >> row >> col) {
        // If successful, return true to indicate valid input
        return true;
    }

    // If extraction was unsuccessful, print an error message
    std::cout << "Invalid move!" << std::endl;

    // Return false to indicate invalid input
    return false;
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
// A unified function to send data to clients
void sendData(const int clientSocket1, const int clientSocket2, char player1, char player2, std::string& board)
{
	std::string board1 = board + "\nServer: Player " +  std::string(1,player1) + " make move:";
	std::string board2 = board + "\nServer: Player " + std::string(1,player2) + " please whait...";
	send(clientSocket1, board1.c_str(), board1.size(), 0);
	send(clientSocket2, board2.c_str(), board2.size(), 0);
}

void sendRecv(int client, std::vector<std::vector<char>>& board, const char player)
{
    bool gameOver{false};  // A flag to track if the game is over
    char buffer[1024];     // Buffer for receiving and sending data
    char winner{};         // To store the winner of the game (initially empty)

    while (!gameOver) {
        char buffeddr[1024];

        // Receive data from the client and clear the terminal
        recvData(client, buffer, sizeof(buffer));
        system("clear");

        // Display the received data
        std::cout << buffer << std::endl;

        // Determine the last character received
        size_t last = std::strlen(buffer);

        // Check if the received data indicates the player's turn
        if (last > 0 && buffer[last - 1] == ':') {
            std::string message;
            do {
                std::getline(std::cin, message);
                if (message == "exit") break;
            } while (!processMove(message, board, player));

            // Send the player's move to the client
            send(client, message.c_str(), message.size(), 0);

            if (message == "exit") break;

            // Check if the game is over due to a win
            gameOver = checkWin(board);

            if (gameOver) {
                winner = player;
            }
        } else {
            // Receive data indicating the other player's move
            recvData(client, buffer, sizeof(buffer));
            char player2 = (player == 'X' ? 'O' : 'X');
            std::cout << player2 << "  made a move " << std::endl;

            // Process the received move
            std::string tmp = std::string(buffer);
            processMove(tmp, board, player2);

            // Check if the game is over due to a win
            gameOver = checkWin(board);

            if (gameOver) {
                winner = player2;
            }
        }
    }

    // Receive final data and clear the terminal
    recvData(client, buffer, sizeof(buffer));
    system("clear");

    // Display the final data
    std::cout << buffer << std::endl;

    // Display the game result
    if (winner == player) {
        std::cout << "___You won___" << std::endl;
    } else {
        std::cout << "___You lose___" << std::endl;
    }
    std::cout << "__GAME OVER__" << std::endl;
}
bool processMove(const std::string& input, std::vector<std::vector<char>>& board, const char player)
{
    int row{}, col{};
    
    // Try to convert the input string to row and col using 'toInt' function
    if (!toInt(input, row, col)) {
        return false; // If conversion fails, the input is invalid
    }
    
    // Check if the row and col values are within the valid range and the cell is not already occupied
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        std::cout << "Invalid move. Try again. Utility.cpp" << std::endl;
        return false; // If move is invalid, return false
    }
    
    // Update the game board with the player's move
    board[row][col] = player;

    return true; // Return true to indicate a successful move
}


void play(int clientSocket1, int clientSocket2, TicTacToe& game)
{
    bool flag = true; // A flag to determine the current player (true for player 1, false for player 2)
    bool gameOver{false}; // A flag to track if the game is over
    std::string board; // A string to hold the current game board

    while (!gameOver) {
        board = game.displayBoard(); // Get the current state of the game board
        std::cout << board << std::endl;

        char buffer[1024]; // A buffer for sending and receiving data
        int row{}, col{}; // Variables to store the row and column of the player's move

        if (flag) {
            flag = false;

            // Send data to player 1 and receive their move
            sendData(clientSocket1, clientSocket2, 'X', 'O', board);
            recvData(clientSocket1, buffer, sizeof(buffer));

            // Convert the received data to row and column
            toInt(std::string(buffer), row, col);

            // Make the move on the game board for player 1 (X)
            game.makeMove(row, col, 'X', gameOver);

            // Send player 1's move to player 2
            send(clientSocket2, buffer, sizeof(buffer), 0);
        } else {
            flag = true;

            // Send data to player 2 and receive their move
            sendData(clientSocket2, clientSocket1, 'O', 'X', board);
            recvData(clientSocket2, buffer, sizeof(buffer));

            // Convert the received data to row and column
            toInt(std::string(buffer), row, col);

            // Make the move on the game board for player 2 (O)
            game.makeMove(row, col, 'O', gameOver);

            // Send player 2's move to player 1
            send(clientSocket1, buffer, sizeof(buffer), 0);
        }

        system("clear"); // Clear the terminal

        board = game.displayBoard(); // Get the updated game board
    }

    // Display the final game board
    std::cout << board << std::endl;

    // Display a game over message
    std::cout << "\n__GAME OVER__" << std::endl;

    // Send the final game board to both players
    send(clientSocket1, board.c_str(), board.size(), 0);
    send(clientSocket2, board.c_str(), board.size(), 0);
}

