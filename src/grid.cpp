#include "grid.h"
#include <iostream>
std::vector<std::vector<Cell>> Grid::grid(Grid::GRID_SIZE, std::vector<Cell>(Grid::GRID_SIZE, Cell(false, 0.0f, 0.0f)));

void Grid::buildGrid(AStar* A) {
    for (int x = 0; x < Grid::GRID_SIZE; x++) {
        for (int y = 0; y < Grid::GRID_SIZE; y++) {
            Cell& cell = grid[x][y];
            cell = Cell(false,x,y);
            std::cout << "Pushing Cell" << std::endl;
            A->getPrio()->push(&cell.node);
            glPushMatrix();
            glTranslatef(x * Grid::CELL_SIZE, y * Grid::CELL_SIZE, 0.0f);
            glBegin(GL_QUADS);
            glColor3f(cell.color[0], cell.color[1], cell.color[2]);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(Grid::CELL_SIZE, 0.0f);
            glVertex2f(Grid::CELL_SIZE, Grid::CELL_SIZE);
            glVertex2f(0.0f, Grid::CELL_SIZE);
            glEnd();
            glPopMatrix();
        }
    }
}
