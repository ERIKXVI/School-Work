#include "snake.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

Snake::Snake(int width, int height) : width(width), height(height), gameOver(false), nTail(0), score(0), tailX(new int[width * height]), tailY(new int[width * height])
{
    srand(time(nullptr));
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}

Snake::~Snake()
{
    delete[] tailX;
    delete[] tailY;
}

void Snake::draw()
{
    system("cls"); // Clear the console screen
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool printed = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        printed = true;
                    }
                }
                if (!printed)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Snake::input(char key)
{
    switch (key)
    {
    case 'a':
        if (dir != Direction::RIGHT)
            dir = Direction::LEFT;
        break;

    case 'd':
        if (dir != Direction::LEFT)
            dir = Direction::RIGHT;
        break;

    case 'w':
        if (dir != Direction::DOWN)
            dir = Direction::UP;
        break;

    case 's':
        if (dir != Direction::UP)
            dir = Direction::DOWN;
        break;

    case 'x':
        gameOver = true;
        break;
    }
}

void Snake::move() {
    // Move the tail
    if (nTail > 0) {
        int prevX = tailX[0];
        int prevY = tailY[0];
        tailX[0] = x;
        tailY[0] = y;
        int tempX, tempY;
        for (int i = 1; i < nTail; i++) {
            tempX = tailX[i];
            tempY = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = tempX;
            prevY = tempY;
        }
    }

    // Move the head
    switch (dir) {
    case Direction::LEFT:
        x--;
        break;
    case Direction::RIGHT:
        x++;
        break;
    case Direction::UP:
        y--;
        break;
    case Direction::DOWN:
        y++;
        break;
    default:
        break;
    }

    // Check for collision with fruit
    if (x == fruitX && y == fruitY) {
        score++;
        nTail++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

    // Check for collision with tail or wall
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
    if (x < 0 || x >= width || y < 0 || y >= height) {
        gameOver = true;
    }
}

bool Snake::checkCollision(int headX, int headY)
{
    // Check for collision with walls
    if (headX >= width || headX < 0 || headY >= height || headY < 0)
    {
        return true;
    }

    // Check for collision with tail
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == headX && tailY[i] == headY)
        {
            return true;
        }
    }

    return false;
}

int Snake::getScore()
{
    return score;
}

bool Snake::isGameOver()
{
    return gameOver;
}
