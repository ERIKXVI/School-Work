#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
	Snake(int width, int height);
	~Snake();
	void draw();
	void input(char key);
	void move();
	bool checkCollision(int headX, int headY);
	int getScore();
	bool isGameOver();

private:
	int x, y;
	int* tailX, * tailY;
	int nTail;
	enum class Direction
	{
		STOP, LEFT, RIGHT, UP, DOWN
	};
	Direction dir;
	const int width;
	const int height;
	int fruitX, fruitY;
	int score;
	bool gameOver;

};
#endif // SNAKE_H
