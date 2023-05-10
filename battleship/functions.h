#pragma once

int BOARD_SIZE = 9;
char** arr = new char* [BOARD_SIZE];
int* shipSizes = new int[4];
const int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;

void printBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
}

void getPlayerShips()
{
	int currX = 0, currY = 0, key;

	key = _getch();
	if (key == 224)
	{
		key = _getch();

		switch (key)
		{
		case UP:
			currY--;
			break;

		case DOWN:
			currY++;
			break;

		case LEFT:
			currX--;
			break;

		case RIGHT:
			currX++;
			break;

		case 13:
			break;
		}
	}
}