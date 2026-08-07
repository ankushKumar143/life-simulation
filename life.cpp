#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>
#include <random>
#include <ctime>

using namespace std;

enum CellState
{
    DEAD = 0,
    ALIVE = 1
};

const int GRID_SIZE = 25;
vector<vector<int>> grid(GRID_SIZE, vector<int>(GRID_SIZE, DEAD));

int countNeighbors(int row, int col)
{
    int count = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int newRow = row + i;
            int newCol = col + j;
            if (newRow < 0 || newRow > GRID_SIZE - 1 || newCol < 0 || newCol > GRID_SIZE - 1)
            {
                continue;
            }
            if (grid[newRow][newCol] == ALIVE)
            {
                count++;
            }
        }
    }
    return count;
}

void updateGrid()
{
    // nextGrid banao
    vector<vector<int>> nextGrid(GRID_SIZE, vector<int>(GRID_SIZE, DEAD));

    // Har row aur column visit karo
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            int neighbors = countNeighbors(i, j);
            if (grid[i][j] == ALIVE)
            {
                if (neighbors < 2)
                {
                    nextGrid[i][j] = DEAD;
                }
                else if (neighbors > 3)
                {
                    nextGrid[i][j] = DEAD;
                }
                else
                {
                    nextGrid[i][j] = ALIVE;
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    nextGrid[i][j] = ALIVE;
                }
            }
        }
    }
    grid = nextGrid;
}

void printGrid()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == ALIVE)
                cout << "█ ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

void clearScreen()
{
    system("cls");
}

void initializeBlinker()
{
    grid[10][10] = ALIVE;
    grid[10][11] = ALIVE;
    grid[10][12] = ALIVE;
}

void initializeGlider()
{
    grid[1][2] = ALIVE;

    grid[2][3] = ALIVE;

    grid[3][1] = ALIVE;
    grid[3][2] = ALIVE;
    grid[3][3] = ALIVE;
}

void initializeBeacon()
{
    grid[0][0] = ALIVE;
    grid[0][1] = ALIVE;
    grid[1][0] = ALIVE;
    grid[1][1] = ALIVE;
    grid[2][2] = ALIVE;
    grid[2][3] = ALIVE;
    grid[3][2] = ALIVE;
    grid[3][3] = ALIVE;
}

void initializeToad()
{
    grid[0][1] = ALIVE;
    grid[0][2] = ALIVE;
    grid[1][0] = ALIVE;
    grid[1][1] = ALIVE;
    grid[1][2] = ALIVE;
}

void initializeRandom()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = rand() % 2;
        }
    }
}

int countAliveCells()
{
    int count = 0;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == ALIVE)
            {
                count++;
            }
        }
    }
    return count;
}

int main()
{
    srand(time(nullptr));
    clearScreen();
    // menu
    int choice;
    cout << "=====================================" << endl;
    cout << "         Conway's Game of Life       " << endl;
    cout << "=====================================" << endl;
    cout << "1. Blinker" << endl;
    cout << "2. Glider" << endl;
    cout << "3. Beacon" << endl;
    cout << "4. Toad" << endl;
    cout << "5. Random" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        initializeBlinker();
        break;
    case 2:
        initializeGlider();
        break;
    case 3:
        initializeBeacon();
        break;
    case 4:
        initializeToad();
        break;
    case 5:
        initializeRandom();
        break;
    default:
        cout << "Invalid choice" << endl;
        return 0;
    }

    int count = 1;

    while (true)
    {
        cout << "=====================================" << endl;
        cout << "         Conway's Game of Life       " << endl;
        cout << "=====================================" << endl;
        cout << "Generation: " << count << endl;
        cout << "Alive cells: " << countAliveCells() << endl;

        printGrid();

        updateGrid();

        Sleep(300); // 500 milliseconds

        clearScreen();

        count++;
    }

    return 0;
}
