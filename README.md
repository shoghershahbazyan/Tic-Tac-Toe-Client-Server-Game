 # Tic-Tac-Toe
Tic-Tac-Toe Console Game

## Game description

### Game Board and Display:
- [x] The game provides a 3x3 grid for playing tic-tac-toe.
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




