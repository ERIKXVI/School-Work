#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <vector>

class BattleshipGame {
private:
    int boardSize;
    std::vector<std::vector<char>> board;
    const char EMPTY_CELL = '-';
    const char SHIP_CELL = 'S';

public:
    BattleshipGame(); // Default constructor
    BattleshipGame();
    void initializeBoard();
    void printBoard();
    void placeShips();
    void play();
};

#endif // BATTLESHIP_H
