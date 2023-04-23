#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
	public:
		Snake(int witdh, int height);
		void draw();
		void input();
		void move();
		bool checkCollision();
		int getScore();
		bool isGameOver();

	private:
		int x, y;
		int tailX[100], tailY[100];
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

#endif // !SNAKE_H

