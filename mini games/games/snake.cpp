#include "snake.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

Snake::Snake(int witdh, int height) : width(witdh), height(height), gameOver(false)
{
	srand(time(nullptr));
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	dir = Direction::STOP;
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

void Snake::input()
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

void Snake::move()
{
    // Move the tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move the head
    switch (dir)
    {
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

    // Check if snake is out of bounds
    if (x < 0 || x> width || y < 0 || y > height)
		gameOver = true;

    // Check if snake eats fruit
    if (x == fruitX && y == fruitY)
    {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

    // Check if snake collides with itself
	for (int i = 0; i < nTail; i++)
    { 
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
}
		