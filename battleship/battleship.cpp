#include <iostream>
#include <conio.h>
using namespace std;
#include "functions.h"

int main()
{
	for (int i = 0; i < BOARD_SIZE; i++) arr[i] = new char[BOARD_SIZE];

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (j == 0 && i != 0) arr[i][j] = i + 64;
			else if (i == 0 && j != 0) arr[i][j] = j + 48;
			else arr[i][j] = ' ';
		}
	}

	printBoard();

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}