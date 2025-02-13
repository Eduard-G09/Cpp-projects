#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver;
int snakeX, snakeY, fruitX, fruitY, score;
const int width = 40;
const int height = 20;

enum Direction { stop = 0, left, right, up, down};
Direction dir;

int lTail=0;
int tailX[100], tailY[100];

void Setup()
{
	gameOver = false;
	dir = stop;
	snakeX = width / 2;
	snakeY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width+2; i++)
	{
		std::cout << "*";
	}
	std::cout << std::endl;

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				std::cout << "*";
			}
			if (i == snakeY && j == snakeX)
			{
				std::cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				std::cout << '&';
			}
			else
			{
				bool print = false;
				for (int k = 0; k < lTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						std::cout << "o";
					}
				}
				if (!print)
				{
					std::cout << " ";
				}
			}
				
			if (j == width - 1)
				std::cout << "*";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width+2; i++)
	{
		std::cout << "*";
	}
	std::cout << std::endl;

	std::cout << "Score: " << score << std::endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a': dir = left;
			break;

		case 'w': dir = up;
			break;

		case 's': dir = down;
			break;

		case 'd': dir = right;
			break;

		case 0x48: dir = up;
			break;

		case 0x50: dir = down;
			break;

		case 0x4B: dir = left;
			break;

		case 0x4D: dir = right;
			break;

		case 'x': gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevPozX = tailX[0];
	int prevPozY = tailY[0];
	int prev2PozX, prev2PozY;
	tailX[0] = snakeX;
	tailY[0] = snakeY;

	for (int i = 1; i < lTail; i++)
	{
		prev2PozX = tailX[i];
		prev2PozY = tailY[i];
		tailX[i] = prevPozX;
		tailY[i] = prevPozY;
		prevPozX = prev2PozX;
		prevPozY = prev2PozY;
	}

	switch(dir)
	{
	case left: snakeX--;
		break;

	case right: snakeX++;
		break;

	case up: snakeY--;
		break;

	case down: snakeY++;
		break;

	}

	if (snakeX == fruitX && snakeY == fruitY)
	{
		score += 50;
		fruitX = rand() % width;
		fruitY = rand() % height;
		lTail++;
	}

	if (snakeX > width)
		snakeX = 0;
	
	if (snakeX < 0)
		snakeX = width - 1;
	
	if (snakeY > height)
		snakeY = 0;
	
	if (snakeY < 0)
		snakeY = height - 1;
	
	for (int i = 0; i < lTail; i++)
	{
		if (tailX[i] == snakeX && tailY[i] == snakeY)
		{
			gameOver= true;
		}
	}
	
	
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	std::cin.get();
	
	return 0;
}