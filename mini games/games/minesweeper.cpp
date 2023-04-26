#include "minesweeper.h"
#include <cstdlib>
#include <ctime>

Minesweeper::Minesweeper(int rows, int cols, int num_mines) {
    this->rows = rows;
    this->cols = cols;
    this->num_mines = num_mines;
    num_revealed = 0;
    gameOver = false;
    gameWon = false;
    board = vector<vector<char>>(rows, vector<char>(cols, '-'));
    revealed = vector<vector<bool>>(rows, vector<bool>(cols, false));
    srand(time(NULL));
}

void Minesweeper::placeMines(pair<int, int> firstClick) {
    int num_placed = 0;

    while (num_placed < num_mines) {
        int row = rand() % rows;
        int col = rand() % cols;

        // Don't place mine on first click or on an already placed mine
        if (mines.count({ row, col }) == 0 && make_pair(row, col) != firstClick) {
            mines.insert(make_pair(row, col));
            num_placed++;
        }
    }
}

void Minesweeper::printBoard() {
    cout << "  ";
    for (int i = 0; i < cols; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < rows; i++) {
        cout << i << " ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void Minesweeper::floodFill(int x, int y) {
    // check if cell is already revealed or is flagged
    if (grid[x][y].revealed || grid[x][y].flagged) {
        return;
    }

    // reveal cell
    grid[x][y].revealed = true;
    numUnrevealed--;

    // check if cell has a bomb nearby
    if (grid[x][y].value == -1) {
        gameOver = true;
        return;
    }

    // if cell has no bombs nearby, recursively floodfill its neighbors
    if (grid[x][y].value == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int neighborX = x + i;
                int neighborY = y + j;
                if (neighborX >= 0 && neighborX < size && neighborY >= 0 && neighborY < size) {
                    floodfill(neighborX, neighborY);
                }
            }
        }
    }
}

void Minesweeper::play() {
    // initialize game
    init();

    // main game loop
    while (!gameOver) {
        draw();
        int x, y;
        cout << "Enter coordinates (row, column): ";
        cin >> x >> y;

        // check if cell is valid
        if (x >= 0 && x < size && y >= 0 && y < size) {
            // check if cell is already revealed or is flagged
            if (grid[x][y].revealed || grid[x][y].flagged) {
                cout << "Cell is already revealed or is flagged!" << endl;
            }
            // if cell has a bomb, game over
            else if (grid[x][y].value == -1) {
                gameOver = true;
            }
            // if cell has no bombs nearby, recursively reveal its neighbors
            else if (grid[x][y].value == 0) {
                floodfill(x, y);
            }
            // otherwise, reveal the cell
            else {
                grid[x][y].revealed = true;
                numUnrevealed--;
            }
        }
        else {
            cout << "Invalid coordinates!" << endl;
        }
    }

    // game over, reveal all cells and draw the final state
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j].revealed = true;
        }
    }
    draw();
    cout << "Game over!" << endl;
}