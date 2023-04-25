#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include <vector>

using namespace std;

class Minesweeper {
private:
    vector<vector<char>> board;
    vector<vector<bool>> revealed;
    vector<pair<int, int>> mines;
    int rows;
    int cols;
    int num_mines;
    int num_revealed;
    bool gameOver;
    bool gameWon;

    void printBoard();
    void placeMines(pair<int, int> firstClick);
    void floodFill(int row, int col);

public:
    Minesweeper(int rows, int cols, int num_mines);
    void play();
};

#endif
