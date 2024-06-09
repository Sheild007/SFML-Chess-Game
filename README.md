# Chess Game

## Overview

This project is a C++ implementation of a chess game. It includes all standard chess pieces and follows the rules of chess. The game features functionalities such as check, checkmate, castling, and pawn promotion. The graphical interface is managed using the SFML library.

## Features

- Full implementation of chess rules
- Graphical interface using SFML
- Player vs. Player mode
- Check and Checkmate detection
- Castling and Pawn Promotion
- Save and Load game states

## Installation

### Prerequisites

- [SFML Library](https://www.sfml-dev.org/download.php) (Simple and Fast Multimedia Library)
- C++ compiler (e.g., g++, clang++)
- Make sure you have git installed
- ./ChessGame


### Clone the Repository

```sh
git clone https://github.com/yourusername/ChessGame.git
cd ChessGame
```


### Building the Project

1. **Install SFML**:
   Follow the instructions on the SFML website to install the library on your system. Ensure that the SFML library files are correctly linked to your project.

2. **Compile the Project**:
   Ensure you have a C++ compiler installed. Run the following commands in your project directory to compile the project:

   ```sh
   g++ -c *.cpp -I/path/to/sfml/include
   g++ -o ChessGame *.o -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
   ```
## Usage

Once the game starts, you can play chess in a player vs. player mode. Use the graphical interface to select and move pieces according to standard chess rules.

### Controls

- Click on a piece to select it.
- Click on a valid destination square to move the selected piece.
- The game will automatically handle special rules such as castling and pawn promotion.

### Game States

- **Check**: The game will notify you if a king is in check.
- **Checkmate**: The game will end if a king is in checkmate.
- **Stalemate**: The game will notify you if there is a stalemate.
- **Castling**: Castling is supported if neither the king nor the rook involved has moved previously.
- **Pawn Promotion**: When a pawn reaches the opposite end of the board, it can be promoted to a queen, rook, bishop, or knight.

## Project Structure

- **Bishop.h, Bishop.cpp**: Implementation of the Bishop piece.
- **Board.h, Board.cpp**: Manages the chessboard, pieces, and game logic.
- **Chess.h, Chess.cpp**: Main game class that controls the game flow.
- **ChessGameState.h, ChessGameState.cpp**: Handles the state of the game for saving and loading purposes.
- **King.h, King.cpp**: Implementation of the King piece.
- **Knight.h, Knight.cpp**: Implementation of the Knight piece.
- **Pawn.h, Pawn.cpp**: Implementation of the Pawn piece.
- **Piece.h, Piece.cpp**: Base class for all pieces.
- **Players.h, Players.cpp**: Manages player information.
- **Position.h, Position.cpp**: Manages positions on the chessboard.
- **Queen.h, Queen.cpp**: Implementation of the Queen piece.
- **Rook.h, Rook.cpp**: Implementation of the Rook piece.
- **Utility.h**: Contains utility functions and enums.

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/Sheild007/SFML-Chess-Game?tab=MIT-1-ov-file) file for details.

## Acknowledgements

- SFML Library for providing the graphical interface tools.

## Contact

If you have any questions or feedback, feel free to reach out to [usmuneer19741974@gmail.com](mailto:usmuneer19741974@gmil.com).


   


