#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>

class TicTacToe {
public:
    TicTacToe();
    // Method to display the current game board
    std::string displayBoard(); 
    // Method to make a move on the board
    bool makeMove(int row, int col); 
    // Method to check if the game has been won
    bool checkWin();
    // Method to check if the game is a draw
    bool checkDraw();
 
    // Method to start the game
    void playGame();
    // Method to make one move
    void makeMove(const int, const int, char, bool&);
    private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
};

#endif // GAME_H
