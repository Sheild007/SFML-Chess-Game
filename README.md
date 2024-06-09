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
### Building the Project

1. **Install SFML**:
   Follow the instructions on the SFML website to install the library on your system. Ensure that the SFML library files are correctly linked to your project.

2. **Compile the Project**:
   Ensure you have a C++ compiler installed. Run the following commands in your project directory to compile the project:

   ```sh
   g++ -c *.cpp -I/path/to/sfml/include
   g++ -o ChessGame *.o -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system


