#include <iostream>
#include <string>
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
bool initGameLoop = false;


void displayProlog();
// merge initBoard and Draw sanke as it has to be drawn in same loop
void initBoard();
void drawSnake();
bool askQuestionYN(const std::string Question);
inline void clearScreen();

int main()
{
	displayProlog();
	initGameLoop = askQuestionYN("Do you wish to start game?");

	while (initGameLoop)
	{
		clearScreen();
		initBoard();
		drawSnake();

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

void drawSnake()
{
	std::cout << "@";
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