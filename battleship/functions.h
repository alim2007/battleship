#pragma once

int BOARD_SIZE = 10; // eslinde 9, 1-ci row ve col koordinatlardir
char** arr = new char* [BOARD_SIZE]; // player board
const int shipCount = 10;
int* shipSizes = new int[shipCount] {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
const int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13, SPACE = 32;

void showMainMenu(int currOption) {
    cout << "=== MAIN MENU ===" << '\n';
    cout << (currOption == 0 ? "> " : "  ") << "New Game" << '\n';
    cout << (currOption == 1 ? "> " : "  ") << "Help" << '\n';
    cout << (currOption == 2 ? "> " : "  ") << "Exit" << '\n';
}

void showSubMenu(int currOption)
{
    cout << (currOption == 0 ? "> " : "  ") << "Place ships manually" << '\n';
    cout << (currOption == 1 ? "> " : "  ") << "Place ships randomly" << '\n';
    cout << (currOption == 2 ? "> " : "  ") << "Back to main menu" << '\n';
}

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

bool isValid(int x, int y, int currShipSizeIndex, bool isHorizontal)
{
    int shipSize = shipSizes[currShipSizeIndex];

    //// Check all cells around the ship's placement coordinates
    //for (int i = y - 1; i <= y + 1; i++)
    //{
    //    for (int j = x - 1; j <= x + shipSize; j++)
    //    {
    //        // Skip the cell if it is out of bounds
    //        if (i < 0 || i >= BOARD_SIZE || j < 0 || j >= BOARD_SIZE)
    //            continue;

    //        // Skip the current cell
    //        if (i == y && j >= x && j < x + shipSize)
    //            continue;

    //        // Check if the cell contains a ship
    //        if (arr[i][j] == 'S')
    //            return false;
    //    }
    //}

    if (isHorizontal)
    {
        if (x + shipSizes[currShipSizeIndex] >= BOARD_SIZE) return false;    
        
        else 
        {
            for (int i = 0; i < shipSizes[currShipSizeIndex]; i++) 
            {
                if (arr[y][x + i] == 'S' ||
                    (y > 0 && arr[y - 1][x + i] == 'S') ||
                    (y < BOARD_SIZE - 1 && arr[y + 1][x + i] == 'S')) 
                {
                    return false;
                }
            }
        }
    }

    else
    {
        if (y + shipSizes[currShipSizeIndex] >= BOARD_SIZE) return false;

        else
        {
            for (int i = 0; i < shipSizes[currShipSizeIndex]; i++)
            {
                if (arr[y + i][x] == 'S' ||
                    (x > 0 && arr[y + i][x - 1] == 'S') ||
                    (x < BOARD_SIZE - 1 && arr[y + i][x + 1] == 'S'))
                {
                    return false;
                }
            }
        }
    }

    return true;
}


void updateBoard(int x, int y, int copyX, int copyY, int currShipSizeIndex, bool final, bool isHorizontal)
{
	int shipSize = shipSizes[currShipSizeIndex];

	if (!final)
	{
		for (int i = 0; i < shipSize; i++)
		{
			arr[copyY][copyX] = ' ';
            if (isHorizontal) copyX++;
            else copyY++;
		}
	}

	for (int i = 0; i < shipSize; i++)
	{
		if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
		{
			arr[y][x] = 'S';
		}

        if (isHorizontal) x++;
        else y++;
	}
}

void updateBoard(int x, int y, int copyX, int copyY, int currShipSizeIndex, bool final)
{
    int shipSize = shipSizes[currShipSizeIndex];

    if (!final)
    {
        for (int i = 0; i < shipSize; i++)
        {
            arr[copyY][copyX] = ' ';
            copyX++;
        }
    }

    for (int i = 0; i < shipSize; i++)
    {
        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
        {
            arr[y][x] = 'S';
        }
        x++;
    }
}

void getPlayerShips()
{
    int currX = BOARD_SIZE / 2, currY = BOARD_SIZE / 2, key, currShipSizeIndex = 0;
    int copyX = currX, copyY = currY;
    bool final = false, isHorizontal = true;

    while (currShipSizeIndex < shipCount)
    {
        system("cls");
        printBoard();
        key = _getch();
        if (key == 224 || key == SPACE)
        {
            key = _getch();

            switch (key)
            {
            case UP:
                //cout << "in up key";
                //_getch();
                copyX = currX, copyY = currY;
                if (!isValid(currX, currY - 1, currShipSizeIndex, isHorizontal)) break;
                currY--;
                break;

            case DOWN:
                //cout << "in down key";
                //_getch();
                copyX = currX, copyY = currY;
                if (!isValid(currX, currY + 1, currShipSizeIndex, isHorizontal)) break;
                currY++;
                break;

            case LEFT:
                //cout << "in left key";
                //_getch();
                copyX = currX, copyY = currY;
                if (!isValid(currX, currX - 1, currShipSizeIndex, isHorizontal)) break;
                currX--;
                break;

            case RIGHT:
                //cout << "in right key";
                //_getch();
                copyX = currX, copyY = currY;
                if (!isValid(currX, currX + 1, currShipSizeIndex, isHorizontal)) break;
                currX++;
                break;

            case SPACE:
                copyX = currX, copyY = currY;
                isHorizontal = !isHorizontal;
                break;
            }
            updateBoard(currX, currY, copyX, copyY, currShipSizeIndex, false, isHorizontal);
        }
        else if (key == ENTER)
        {
            //cout << "before valid";
            //_getch();
            if (isValid(currX, currY, currShipSizeIndex, isHorizontal))
            {
                //cout << "in valid";
                //_getch();
                updateBoard(currX, currY, copyX, copyY, currShipSizeIndex, true, isHorizontal);
            }
            currShipSizeIndex++;
            currX = BOARD_SIZE / 2;
            currY = BOARD_SIZE / 2;
            copyX = currX;
            copyY = currY;
        }
        
    }
}

void getPlayerShipsRand()
{
    int currShipSizeIndex = 0;

    while (currShipSizeIndex < shipCount) 
    {
        int rX = rand() % (BOARD_SIZE - 1) + 1;
        int rY = rand() % (BOARD_SIZE - 1) + 1;
        bool isHorizontal = rand() % 2 == 0;
        bool valid = isValid(rX, rY, currShipSizeIndex, isHorizontal);

        if (valid) 
        {
            updateBoard(rX, rY, rX, rY, currShipSizeIndex, true, isHorizontal);
            currShipSizeIndex++;
        }
    }
}

void menu()
{

}