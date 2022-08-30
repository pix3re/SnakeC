#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

/* display prolog 
* draw board
* draw snake
* draw food
* do logic
* draw game info
*/

int BOARD_WIDTH = 25;
int BOARD_HEIGHT = 25;

int FRUIT_X, FRUIT_Y;
int SNAKE_H[2] = { BOARD_WIDTH / 2, BOARD_HEIGHT / 2 };

bool initGameLoop = false;


void displayProlog();
// merge initBoard and Draw sanke as it has to be drawn in same loop
void initBoard();
void setupGameVariables();
bool askQuestionYN(const std::string Question);
inline void clearScreen();

int main()
{
	displayProlog();
	initGameLoop = askQuestionYN("Do you wish to start game?");

	if (initGameLoop)
	{
		setupGameVariables();
	}

	while (initGameLoop)
	{
		clearScreen();
		initBoard();

		Sleep(1000);
	}

	return 0;
}

void displayProlog()
{
	std::cout << "Welcom to Snake! This is console based game." << std::endl;
	std::cout << "Basic rules is to get as many scores as possible." << std::endl;
	std::cout << "Basic movement can be done using A, W, S, D keys." << std::endl;
	std::cout << std::endl;
}

void setupGameVariables()
{
	std::srand(std::time(0));

	FRUIT_X = std::rand() % BOARD_WIDTH;
	FRUIT_Y = std::rand() % BOARD_HEIGHT;
}

void initBoard()
{
	for (int x = 0; x <= BOARD_WIDTH; x++)
	{
		for (int y = 0; y <= BOARD_HEIGHT; y++)
		{
			//std::cout << "[" << x << "," << y << "]";
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
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
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