#include "Grid.h"
#include "CellState.h"

Grid::Grid()
    : grid(GRID_SIZE, std::vector<int>(GRID_SIZE, DEAD))
{
}

int Grid::getSize() const
{
    return GRID_SIZE;
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