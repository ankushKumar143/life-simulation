#include "Grid.h"
#include "CellState.h"
#include <random>

//! Initialize the grid with every cell in the DEAD state
Grid::Grid()
    : grid(GRID_SIZE, std::vector<int>(GRID_SIZE, DEAD))
{
}

//! Count the total number of alive cells in the grid
int Grid::countAliveCells() const
{
    int count = 0;

    //! Visit every cell in the grid
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            //! Increase the count if the cell is alive
            if (grid[i][j] == ALIVE)
            {
                count++;
            }
        }
    }

    return count;
}

//! Load one of the predefined or random patterns
void Grid::loadPattern(Pattern pattern)
{
    //! Clear the existing grid before loading a new pattern
    clear();

    switch (pattern)
    {
    case Pattern::Blinker:
        //! Horizontal three-cell oscillator
        setAlive(10, 10);
        setAlive(10, 11);
        setAlive(10, 12);
        break;

    case Pattern::Glider:
        //! Small pattern that moves diagonally across the grid
        setAlive(1, 2);
        setAlive(2, 3);
        setAlive(3, 1);
        setAlive(3, 2);
        setAlive(3, 3);
        break;

    case Pattern::Beacon:
        //! Two blocks that alternate between alive and dead states
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
        //! Six-cell oscillator
        setAlive(0, 1);
        setAlive(0, 2);

        setAlive(1, 0);
        setAlive(1, 1);
        setAlive(1, 2);
        break;

    case Pattern::Random:
    {
        //! Create a random number generator
        std::random_device rd;
        std::mt19937 generator(rd());

        //! Generate either 0 (DEAD) or 1 (ALIVE)
        std::uniform_int_distribution<int> distribution(0, 1);

        //! Randomly set the state of every cell
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
}

//! Return the size of the grid
int Grid::getSize() const
{
    return GRID_SIZE;
}

//! Set every cell in the grid to DEAD
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

//! Switch a cell between ALIVE and DEAD
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

//! Make a specific cell alive
void Grid::setAlive(int row, int col)
{
    grid[row][col] = ALIVE;
}

//! Check whether a specific cell is alive
bool Grid::isAlive(int row, int col) const
{
    return grid[row][col] == ALIVE;
}

//! Count the alive neighbors surrounding a cell
int Grid::countNeighbors(int row, int col) const
{
    int count = 0;

    //! Check all cells in the 3x3 area around the current cell
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // Skip the current cell itself
            if (i == 0 && j == 0)
            {
                continue;
            }

            // Calculate the neighboring cell's position
            int newRow = row + i;
            int newCol = col + j;

            // Ignore positions outside the grid boundaries
            if (newRow < 0 ||
                newRow > GRID_SIZE - 1 ||
                newCol < 0 ||
                newCol > GRID_SIZE - 1)
            {
                continue;
            }

            //! Count the neighbor if it is alive
            if (grid[newRow][newCol] == ALIVE)
            {
                count++;
            }
        }
    }

    return count;
}

//! Calculate the next generation using Conway's Game of Life rules
void Grid::update()
{
    //! Create a separate grid for the next generation
    //! This prevents changes from affecting other cells during the calculation
    std::vector<std::vector<int>> nextGrid(
        GRID_SIZE,
        std::vector<int>(GRID_SIZE, DEAD));

    //! Process every cell in the current grid
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            //! Count the cell's alive neighbors
            int neighbors = countNeighbors(i, j);

            //! Apply rules to an alive cell
            if (grid[i][j] == ALIVE)
            {
                //! Fewer than 2 neighbors → cell dies from underpopulation
                if (neighbors < 2)
                {
                    nextGrid[i][j] = DEAD;
                }

                //! More than 3 neighbors → cell dies from overpopulation
                else if (neighbors > 3)
                {
                    nextGrid[i][j] = DEAD;
                }

                //! 2 or 3 neighbors → cell survives
                else
                {
                    nextGrid[i][j] = ALIVE;
                }
            }
            else
            {
                //! A dead cell with exactly 3 neighbors becomes alive
                if (neighbors == 3)
                {
                    nextGrid[i][j] = ALIVE;
                }
            }
        }
    }

    //! Replace the current generation with the newly calculated generation
    grid = nextGrid;
}