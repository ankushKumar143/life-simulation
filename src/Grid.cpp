#include "Grid.h"
#include "CellState.h"
#include <random>

Grid::Grid()
    : grid(GRID_SIZE, std::vector<int>(GRID_SIZE, DEAD))
{
}

int Grid::countAliveCells() const
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

void Grid::loadPattern(Pattern pattern)
{
    clear();

    switch (pattern)
    {
    case Pattern::Blinker:
        setAlive(10, 10);
        setAlive(10, 11);
        setAlive(10, 12);
        break;

    case Pattern::Glider:
        setAlive(1, 2);
        setAlive(2, 3);
        setAlive(3, 1);
        setAlive(3, 2);
        setAlive(3, 3);
        break;

    case Pattern::Beacon:
        setAlive(0, 0);
        setAlive(0, 1);
        setAlive(1, 0);
        setAlive(1, 1);

        setAlive(2, 2);
        setAlive(2, 3);
        setAlive(3, 2);
        setAlive(3, 3);
        break;

    case Pattern::Toad:
        setAlive(0, 1);
        setAlive(0, 2);

        setAlive(1, 0);
        setAlive(1, 1);
        setAlive(1, 2);
        break;

    case Pattern::Random:
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, 1);

        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                grid[i][j] = distribution(generator);
            }
        }

        break;
    }
}

int Grid::getSize() const
{
    return GRID_SIZE;
}

void Grid::clear()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = DEAD;
        }
    }
}

void Grid::toggleCell(int row, int col)
{
    if (grid[row][col] == ALIVE)
    {
        grid[row][col] = DEAD;
    }
    else
    {
        grid[row][col] = ALIVE;
    }
}

void Grid::setAlive(int row, int col)
{
    grid[row][col] = ALIVE;
}

bool Grid::isAlive(int row, int col) const
{
    return grid[row][col] == ALIVE;
}

int Grid::countNeighbors(int row, int col) const
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

void Grid::update()
{
    std::vector<std::vector<int>> nextGrid(
        GRID_SIZE,
        std::vector<int>(GRID_SIZE, DEAD));

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