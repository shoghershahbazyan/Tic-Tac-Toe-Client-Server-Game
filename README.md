 # Tic-Tac-Toe
Tic-Tac-Toe Console Game

## Game description

### Game Board and Display:
- [*] The game provides a 3x3 grid for playing tic-tac-toe.
- [x] The grid is displayed on the console.
- [x] The grid is labeled with row and column indices to help players select their moves.

### Player Input:
- [x] Players can input their moves in the format (row column) using the console.
- [x] Input is validated to ensure it's within the valid range (0 to 2) and an unoccupied cell.

### Game Logic:
- [x] The game correctly detects a win condition when a player has three consecutive symbols in a horizontal, vertical, or diagonal row.
- [x] The game correctly detects a draw condition when the grid is full, and no player has won.
- [x] The game allows for continuous play until a win or draw occurs.

### Player Turns:
- [x] Players take turns making moves, starting with Player X.
- [x] The game displays the current player's turn (X or O) on the console.

### Game State Display:
- [x] The game continuously displays the state of the board after each move, updating the grid with Xs and Os.

### End Game Display:
- [x] When the game ends (either by a win or a draw), the program displays a message indicating the winner (X or O) or a draw.

### Error Handling:
- [x] The program handles any unexpected user inputs gracefully and provides informative error messages.

## Usage
Certainly, here's a refactored version of the usage instructions for your Tic-Tac-Toe game:

Usage

To play this console-based Tic-Tac-Toe game, follow these steps:

1. Download the Files:
Download all the files in this repository to your computer.
server.cpp
client.cpp
utility.h
game.h
utility.cpp
game.cpp
2. Compile the Source Code:
Open a terminal and navigate to the directory where you have saved the files.
```
g++ -c server.cpp -o server.o
g++ -c client.cpp -o client.o
g++ -c game.cpp -o game.o
g++ -c utility.cpp -o utility.o
```
3. Link the Executable Files:
```
g++ server.o utility.o game.o -o server
g++ client.o utility.o game.o -o client
```
4. Run the Server:
  Start the server by running the following command:
` ./server`
  The server will wait for two players to connect in order to start the game.

5. Run the Clients:
  Players need to join the game by running the following command from separate terminals:
`./client`
  The server will wait for the clients to confirm they are ready to play.
6. Game Start Confirmation:
  The server will prompt the players with the following message:
`Server: Game request: Are you ready to play? (Type 'yes' or 'no')`

7. Gameplay:
  The game board will be displayed, and players take turns to make their moves.
  The game continues until one of the players wins or a draw occurs.
```
-------------
|   |   |   | 
-------------
|   |   |   | 
-------------
|   |   |   | 
-------------

Server: Player X make move:
```
8. End of Game:
  The game will finish when one player wins or when a draw occurs.
  Enjoy playing the game!

## Structure
The game has a class 
class game that provide the game logic

    private:
    TicTacToe(); // Default constructor
    std::string displayBoard(); // Method to display the current game board
    bool makeMove(int row, int col); // Method to make a move on the board
    bool checkWin(); // Method to check if the game has been won
    bool checkDraw(); // Method to check if the game is a draw
    void playGame(); // Method to start the game
    void makeMove(const int, const int, char, bool&); // Method to make one move
   
    private:
    std::vector<std::vector<char>> board;
    char currentPlayer;

    
The utility.cpp file sontaies the helper funtions to play the geme,
```
void recvData(int, char*, size_t);	// Receive data from a socket and handle potential errors.
bool checkReadyStatus(const int, const int);	// Check if both players are ready to start the game.
bool toInt(const std::string&, int&, int&);	// Convert a string input to two integer values.
bool processMove(const std::string&, std::vector<std::vector<char>>&, const char);	// Process a player's move on the game board, returning true if it's valid.
bool checkWin(const std::vector<std::vector<char>>&);	// Check if there's a win condition on the game board, returning true if there's a winner.
void sendData(const int clientSocket1, const int clientSocket2, char player1, char player2, std::string& board);	// Method to send data to palyer
void play(int clientSocket1, int clientSocket2, TicTacToe& game);	// Method to pay a game
void sendRecv(int client, std::vector<std::vector<char>>& board, const char player);	// Method to run the game for client```




