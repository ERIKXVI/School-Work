#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <vector>

const int BOARD_SIZE = 10;
const char EMPTY = '-';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';

class BattleshipGame {
private:
    std::vector<std::vector<char>> board;

public:
    BattleshipGame();

    void placeShips();

    void play();

private:
    void initializeBoard();

    void printBoard();

    bool isCoordinateValid(int row, int col);

    bool isShipPlacementValid(int row, int col, int length, bool isVertical);

    void placeShip(int row, int col, int length, bool isVertical);

    void fireShot(int row, int col);
};

#endif
