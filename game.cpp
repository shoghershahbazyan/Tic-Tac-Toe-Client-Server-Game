#include "game.h"

TicTacToe::TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X') {}

// Method to display the current game board
std::string TicTacToe::displayBoard() 
{
        std::string boardString = "-------------\n";
        for (int i = 0; i < 3; i++) {
            boardString += "| ";
            for (int j = 0; j < 3; j++) {
                boardString += board[i][j];
                boardString += " | ";
            }
            boardString += "\n";
            boardString += "-------------\n";
        }
        return boardString;
    }

// Method to make a move on the board
bool TicTacToe::makeMove(int row, int col)
{
	if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
	    std::cout << "Invalid move. Try again. game.cpp" << std::endl;
	    return false;
	}

	board[row][col] = currentPlayer;
	currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
	return true;
}

// Method to check if the game has been won
bool TicTacToe::checkWin()
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

// Method to check if the game is a draw
bool TicTacToe::checkDraw()
{
	for (int i = 0; i < 3; i++) {
	    for (int j = 0; j < 3; j++) {
		if (board[i][j] == ' ') {
		    return false; // The game is not a draw
		}
	    }
	}
	return true; // The game is a draw
}

// Method to start the game
void TicTacToe::playGame() 
{
	int row, col;
	bool gameWon = false;

	while (true) {
	   std::cout <<  displayBoard() << std::endl;;
	    std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
	    std::cin >> row >> col;

	    if (makeMove(row, col)) {
		if (checkWin()) {
		    std::cout << displayBoard() << std::endl;
		    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
		    std::cout << "Player " << currentPlayer << " wins!" << std::endl;
		    gameWon = true;
		    break;
		} else if (checkDraw()) {
		    std::cout << displayBoard() << std::endl;
		    std::cout << "It's a draw!" << std::endl;
		    break;
		}
	    }
	}

	if (!gameWon) {
	    std::cout << displayBoard() << std::endl;
	}
}

// Method to process one move
void TicTacToe::makeMove(const int row, const int col, char currentPlayer, bool& gameOver) 
{
	   if (makeMove(row, col)) {
		if (checkWin()) {
			std::cout << displayBoard() << std::endl;
			std::cout << "Player " << currentPlayer << " wins!" << std::endl;
		   	gameOver = true;
		} else if (checkDraw()) {
			std::cout << displayBoard() << std::endl;
			std::cout << "It's a draw!" << std::endl;
			gameOver = true;
		}
	}
}
