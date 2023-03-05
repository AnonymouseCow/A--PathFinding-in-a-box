#ifndef GRID_H
#define GRID_H
#include "cell.h"
#include "astarfinder.h"

class Grid {
public:
    static constexpr int GRID_SIZE = 100;    // Number of cells in each dimension
    static constexpr float CELL_SIZE = 0.1f; // Size of each cell in world units
    static constexpr float GRID_WIDTH = GRID_SIZE * CELL_SIZE;
    static constexpr float GRID_HEIGHT = GRID_SIZE * CELL_SIZE;
    static std::vector<std::vector<Cell>> grid; // Initialize all cells to non-obstacle, with default color and position
    static void buildGrid();
};

#endif // GRID_H