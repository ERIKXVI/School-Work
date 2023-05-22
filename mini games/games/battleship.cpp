#include "battleship.h"
#include <iostream>

BattleshipGame::BattleshipGame(int size) {
    boardSize = size;
    board.resize(boardSize, std::vector<char>(boardSize, EMPTY_CELL));
}

void BattleshipGame::initializeBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = EMPTY_CELL;
        }
    }
}

void BattleshipGame::printBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void BattleshipGame::placeShips() {
    int shipCount = boardSize / 2; // Place half the board size number of ships
    int shipSize = 2; // Set ship size to 2 for this example

    for (int i = 0; i < shipCount; i++) {
        int x, y;
        std::cout << "Enter the starting coordinates for Ship " << i + 1 << " (Size: " << shipSize << "): ";
        std::cin >> x >> y;

        if (x >= 0 && x < boardSize && y >= 0 && y < boardSize) {
            // Place ship horizontally
            if (x + shipSize <= boardSize) {
                for (int j = 0; j < shipSize; j++) {
                    board[x + j][y] = SHIP_CELL;
                }
            }
            // Place ship vertically
            else if (y + shipSize <= boardSize) {
                for (int j = 0; j < shipSize; j++) {
                    board[x][y + j] = SHIP_CELL;
                }
            }
            else {
                std::cout << "Invalid ship placement. Try again." << std::endl;
                i--;
            }
        }
        else {
            std::cout << "Invalid coordinates. Try again." << std::endl;
            i--;
        }
    }
}

void BattleshipGame::play() {
    std::cout << "=== BATTLESHIP GAME ===" << std::endl;
    initializeBoard();
    placeShips();

    std::cout << "Game Board:" << std::endl;
    printBoard();
}

int main() {
    int boardSize;
    std::cout << "Enter the board size: ";
    std::cin >> boardSize;

    BattleshipGame game(boardSize);
    game.play();

    return 0;
}
