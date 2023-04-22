#include <iostream>
#include <string>
#include "tictaktoe.h"

using namespace std;

tictactoe::tictactoe()
{
	currentPlayer = 'X';
	isGameOver = false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = '-';
		}
	}
}

void tictactoe::printBoard()
{
	system("cls");
	cout << endl;
	cout << "   0  1  2" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << i << "  ";
		for (int j = 0; j < 3; j++)
		{
			cout << board[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void tictactoe::makeMove()
{
	int row, col;
	cout << "Player " << currentPlayer << ", make your move (row column): ";
	cin >> row >> col;

	if (row < 0 || row > 2 || col < 0 || col > 2)
	{
		cout << "Invalid move. Try again." << endl;
		makeMove();
	}
	else if (board[row][col] != '-')
	{
		cout << "That spot is already taken. Try again." << endl;
		makeMove();
	}
	else
	{
		board[row][col] = currentPlayer;
	}
}

bool tictactoe::checkWin()
{
	// check rows
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
			return true;
		}
	}

	// check columns
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
			return true;
		}
	}

	// check diagonals
	if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		return true;
	}
	if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
		return true;
	}

	return false;
}

void tictactoe::play()
{
	int moveCount = 0;

	while (!isGameOver)
	{
		printBoard();
		makeMove();
		isGameOver = checkWin();
		moveCount++;

		if (isGameOver)
		{
			cout << "Game Over!" << endl;
			cout << "Player " << currentPlayer << " wins!" << endl;
		}
		else if (moveCount == 9)
		{
			cout << "Game Over!" << endl;
			cout << "It's a draw!" << endl;
			isGameOver = true;
		}
		else
		{
			currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
		}
	}
}

