#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>

int BOARD_WIDTH = 25;
int BOARD_HEIGHT = 25;

int FRUIT_X, FRUIT_Y;
int SNAKE_H[2] = { BOARD_WIDTH / 2, BOARD_HEIGHT / 2 };
int SNAKE_TX[100], SNAKE_TY[100];
int nTAIL = 3;
int SCORE = 0;

enum SNAKE_DIRECTION { UP, DOWN, LEFT, RIGHT };

SNAKE_DIRECTION currentDir = DOWN;

bool initGameLoop = true;
bool initProgram = false;


void displayProlog();
void goodbayProlog();
void drawGame();
void handleInput();
void handleGameLogic();
void handleTailLogic();
void setupGameVariables();
void drawFruit();
bool askQuestionYN(const std::string Question);
void gameState(const bool Lost);
void addScore();
void drawScore();
void playAgain();
inline void clearScreen();

int main()
{
	displayProlog();
	initProgram = askQuestionYN("Do you wish to start game?");

	while (initProgram)
	{
		setupGameVariables();

		while (initGameLoop)
		{
			clearScreen();
			drawGame();
			drawScore();
			handleInput();
			handleGameLogic();
			Sleep(300);
		}

		playAgain();
	}

	goodbayProlog();

	return 0;
}

void setupGameVariables()
{
	drawFruit();
	SNAKE_H[0] = BOARD_WIDTH / 2;
	SNAKE_H[1] = BOARD_HEIGHT / 2;
	nTAIL = 3;
	handleTailLogic();
	SCORE = 0;
}

void displayProlog()
{
	std::cout << "Welcom to Snake! This is console based game." << std::endl;
	std::cout << "Basic rules is to get as many scores as possible." << std::endl;
	std::cout << "Basic movement can be done using A, W, S, D keys." << std::endl;
	std::cout << std::endl;
}

void goodbayProlog()
{
	std::cout << "Thank you for playing!" << std::endl;
	std::cout << "We'd hope you come back soon!!" << std::endl;
}

void drawFruit()
{
	std::srand(std::time(0));

	FRUIT_X = std::rand() % BOARD_WIDTH;
	FRUIT_Y = std::rand() % BOARD_HEIGHT;
}

void drawGame()
{
	for (int x = 0; x <= BOARD_WIDTH; x++)
	{
		for (int y = 0; y <= BOARD_HEIGHT; y++)
		{
			if (y == 0 || y == BOARD_HEIGHT || x == 0 || x == BOARD_WIDTH)
			{
				std::cout << "#";
			}
			else if (SNAKE_H[0] == x && SNAKE_H[1] == y)
			{
				std::cout << "@";
			}
			else if (FRUIT_X == x && FRUIT_Y == y)
			{
				std::cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTAIL; k++)
				{
					if (SNAKE_TX[k] == x && SNAKE_TY[k] == y)
					{
						print = true;
						std::cout << "o";
					}
				}
				if (!print)
					std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}

void handleInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (currentDir != DOWN)
				currentDir = UP;
			break;

		case 's':
			if (currentDir != UP)
				currentDir = DOWN;
			break;

		case 'a':
			if (currentDir != RIGHT)
				currentDir = LEFT;
			break;

		case 'd':
			if (currentDir != LEFT)
				currentDir = RIGHT;
			break;
		}
	}
}

void handleTailLogic()
{
	int prevX = SNAKE_TX[0];
	int prevY = SNAKE_TY[0];
	int prevX2, prevY2;
	SNAKE_TX[0] = SNAKE_H[0];
	SNAKE_TY[0] = SNAKE_H[1];

	for (int i = 1; i < nTAIL; i++)
	{
		prevX2 = SNAKE_TX[i];
		prevY2 = SNAKE_TY[i];
		SNAKE_TX[i] = prevX;
		SNAKE_TY[i] = prevY;
		prevX = prevX2;
		prevY = prevY2;
	}
}

void handleGameLogic()
{
	handleTailLogic();

	if (currentDir == UP)
	{
		SNAKE_H[0] = SNAKE_H[0] - 1;
	}
	else if (currentDir == DOWN)
	{
		SNAKE_H[0] = SNAKE_H[0] + 1;
	}
	else if (currentDir == LEFT)
	{
		SNAKE_H[1] = SNAKE_H[1] - 1;
	}
	else if (currentDir == RIGHT)
	{
		SNAKE_H[1] = SNAKE_H[1] + 1;
	}

	if (SNAKE_H[0] == FRUIT_X && SNAKE_H[1] == FRUIT_Y)
	{
		addScore();
		drawFruit();
		nTAIL++;
	}

	if (SNAKE_H[0] < 0 || SNAKE_H[1] == BOARD_WIDTH || SNAKE_H[1] == 0 || SNAKE_H[0] > BOARD_HEIGHT)
	{
		gameState(true);
	}

	for (int k = 0; k < nTAIL; k++)
	{
		if (SNAKE_TX[k] == SNAKE_H[0] && SNAKE_TY[k] == SNAKE_H[1])
		{
			gameState(true);
		}
	}
}

void gameState(const bool Lost)
{
	if (Lost)
	{
		initGameLoop = false;
		clearScreen();
		std::cout << "YOU LOST !!!" << std::endl;
		std::cout << "Scores managed to get: " << SCORE << std::endl;
	}
}

void playAgain()
{
	bool vPlayAgain = askQuestionYN("Do you wish to play again??");
	if (vPlayAgain)
		initGameLoop = true;
	else
		initProgram = false;
}

void addScore()
{
	SCORE += 10;
}

void drawScore()
{
	std::cout << "Score: " << SCORE << std::endl;
}

bool askQuestionYN(const std::string Question)
{
	char vTmp;

	std::cout << Question << " (Y/N)" << std::endl;
	do
	{
		std::cin >> vTmp;
		vTmp = std::tolower(vTmp);

		if (vTmp != 'y' && vTmp != 'n')
		{
			std::cout << "Acceptable input is Y or N, either capital or lower cases. Try again!" << std::endl;
		}
	} 
	while (vTmp != 'y' && vTmp != 'n');

	return vTmp == 'y';
}

inline void clearScreen()
{
	std::system("CLS");
}