#ifndef TICTACTOE_H
#define TICTACTOE_H

class tictactoe
{
public:
	tictactoe();
	void play();

private:
	char board[3][3];
	char currentPlayer;
	bool isGameOver;
	void printBoard();
	void makeMove();
	bool checkWin();
};

#endif // TICTACTOE_H
