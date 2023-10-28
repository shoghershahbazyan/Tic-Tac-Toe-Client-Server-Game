# Tic-Tac-Toe Console Game

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
