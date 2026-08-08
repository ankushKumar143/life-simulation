#pragma once
#include "CellState.h"
#include <vector>

class Grid
{
public:
    Grid();

    void update();
    int getSize() const;

    bool isAlive(int row, int col) const;
    void setAlive(int row, int col);

private:
    int countNeighbors(int row, int col) const;

    static constexpr int GRID_SIZE = 25;
    std::vector<std::vector<int>> grid;
};