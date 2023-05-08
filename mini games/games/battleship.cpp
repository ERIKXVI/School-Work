#include "battleship.h"
#include <iostream>

BattleshipGame::BattleshipGame() {
    initializeBoard();
}

void BattleshipGame::initializeBoard() {
    board.resize(BOARD_SIZE, std::vector<char>(BOARD_SIZE, EMPTY));
}

void BattleshipGame::printBoard() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

bool BattleshipGame::isCoordinateValid(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool BattleshipGame::isShipPlacementValid(int row, int col, int length, bool isVertical) {
    if (isVertical) {
        if (row + length > BOARD_SIZE) {
            return false;
        }
        for (int i = row; i < row + length; i++) {
            if (board[i][col] != EMPTY) {
                return false;
            }
        }
    }
    else {
        if (col + length > BOARD_SIZE) {
            return false;
        }
        for (int j = col; j < col + length; j++) {
            if (board[row][j] != EMPTY) {
                return false;
            }
        }
    }
    return true;
}

void BattleshipGame::placeShip(int row, int col, int length, bool isVertical) {
    if (isVertical) {
        for (int i = row; i < row + length; i++) {
            board[i][col] = SHIP;
        }
    }
    else {
        for (int j = col; j < col + length; j++) {
            board[row][j] = SHIP;
        }
    }
}

void BattleshipGame::placeShips() {
    // Place ships on the board
    placeShip(1, 2, 3, true);  // Vertical ship of length 3 starting from (1, 2)
    placeShip(4, 6, 4, false); // Horizontal ship of length 4 starting from (4, 6)
    placeShip(7, 3, 5, true);  // Vertical ship of length 5 starting from (7, 3)
}

void BattleshipGame::fireShot(int row, int col) {
    if (!isCoordinateValid(row, col)) {
        std::cout << "Invalid coordinates!" << std::endl;
        return;
    }

    if (board[row][col] == EMPTY) {
        std::cout << "Miss!" << std::endl;
        board[row][col] = MISS;
    }
    else if (board[row][col] == SHIP) {
        std::cout << "Hit!" << std::endl;
        board[row][col] = HIT;
    }
    else if (board[row][col] == HIT || board[row][col] == MISS) {
        std::cout << "Already shot at this position!" << std::endl;
    }

    // Check if all ships have been sunk
    bool allShipsSunk = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == SHIP) {
                allShipsSunk = false;
                break;
            }
        }
        if (!allShipsSunk) {
            break;
        }
    }

    if (allShipsSunk) {
        std::cout << "Congratulations! You sunk all the ships!" << std::endl;
    }
}

void BattleshipGame::play() {
    std::cout << "Battleship Game" << std::endl;
    std::cout << "===============" << std::endl;

    placeShips();
    printBoard();

    while (true) {
        int row, col;
        std::cout << "Enter row (0-" << BOARD_SIZE - 1 << "): ";
        std::cin >> row;
        std::cout << "Enter col (0-" << BOARD_SIZE - 1 << "): ";
        std::cin >> col;

        fireShot(row, col);
        printBoard();

        // Check if all ships have been sunk
        bool allShipsSunk = true;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == SHIP) {
                    allShipsSunk = false;
                    break;
                }
            }
            if (!allShipsSunk) {
                break;
            }
        }

        if (allShipsSunk) {
            std::cout << "Congratulations! You sunk all the ships!" << std::endl;
            break;
        }
    }

    std::cout << "Game Over." << std::endl;
}
