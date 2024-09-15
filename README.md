# Chess Game in C++

## Overview
This repository contains a fully functional chess game developed in C++ as part of an introductory programming project. The game allows two players to compete by adhering to the rules of chess, ensuring that only legal moves are allowed, and checking for conditions such as check and checkmate. The graphical interface allows players to visually interact with the board, and optional features include move highlighting, threats visualization, and save/load functionality.

---

## Key Features
- **Playable Chess Game**: A turn-based chess game for two players with a graphical user interface. All standard rules of chess are followed, including valid movements for each piece, checking for check and checkmate conditions, and turn-based play between two players.
  
- **Core Game Logic**:
    - Legal moves for all chess pieces are enforced, including pawns, rooks, knights, bishops, queens, and kings.
    - Special rules such as castling, en passant, and pawn promotion are supported.
    - Check, checkmate, and stalemate conditions are implemented.
  
- **Graphical Interface**: A GUI that visually displays the current state of the chessboard and pieces. This interface updates dynamically as the game progresses.

- **Additional Features**:
    - **Move Highlighting**: Visualize possible moves for a selected piece, highlighting legal and threatened positions.
    - **Save/Load Game**: Save the current state of the game and load it back later for continued play.
    - **Undo/Redo**: Players can undo or redo their last moves, making it easier to recover from mistakes.

---

## Folder Structure

The project is structured in a modular way, with each key component organized in its own folder. This separation helps in maintaining and extending the project, with clear distinctions between the game logic, GUI, and resources.

```bash
chess-game/
├── src/
│   ├── board/
│   │   ├── chessboard.cpp      # Handles drawing the chessboard
│   │   └── chessboard.h
│   ├── game/
│   │   ├── game.cpp            # Core game logic for handling moves and turns
│   │   └── game.h
│   ├── gui/
│   │   ├── mainwindow.cpp      # Handles the GUI and visual interactions
│   │   └── mainwindow.h
│   ├── pieces/
│   │   ├── chesspiece.cpp      # Logic for piece movements and rules
│   │   └── chesspiece.h
│   ├── main.cpp                # Initializes the window and game loop
│   └── resources.h             # Manages resource paths (chess piece SVGs)
├── resources/
│   └── ...                 # Chess piece images in .svg format
```

## Core Game Mechanics

1. **Piece Movement**: Each piece has its own movement rules, which are enforced during gameplay. For example, pawns can move forward one square, rooks can move horizontally or vertically, bishops can move diagonally, etc.
2. **Legal Moves**: Only valid moves are allowed, and players cannot move a piece that would place their own king in check.
3. **Turn-Based Play**: Players take turns moving their pieces, with the game enforcing the order of play.
4. **Check and Checkmate**: The game checks for conditions where a player's king is in check (threatened by an opponent's piece) and if the king is in checkmate (no legal moves can prevent the king from being captured).

## Optional Features

1. **Move Highlighting**: When a piece is selected, the possible legal moves are highlighted on the board.
2. **Save/Load Game**: You can save the current state of the game to a file and load it back later.
3. **Undo/Redo**: Players can undo or redo their last move, offering flexibility in play.
4. **Visual Threats**: Highlight pieces that are under threat from the opponent’s pieces.
