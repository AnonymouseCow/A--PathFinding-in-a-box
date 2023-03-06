
#include "astarfinder.h"
#include "grid.h"
#include <math.h>
#include <queue>
#include <set>
#include <iostream>
std::priority_queue<Cell*, std::vector<Cell*>, NodeCompareA> AStar::open;
std::set<Cell*> AStar::closed;
AStar::AStar() {}
void AStar::findPath(Cell* startCell, Cell* endCell) {
    // Add start node to open list
        std::cout << "Beginning pathfinding..";
        std::cout << "START AT: " << " (" << startCell->x << ", " << startCell->y << ")" << std::endl; 
        startCell->setColor(1.0f,0.0f,0.0f);
        open.push(startCell);
        Cell* current = nullptr;
        while (!open.empty()) {
            current = open.top();
            open.pop();
            closed.insert(current);
            std::cout << "open not empty" << std::endl;
            std::cout << "Node at (" << current->x << ", " << current->y << ") has priority " << current->getNodeAddr()->f << std::endl;
           if (endCell->compareCells(current)) {
               std::cout << "found the end";
                endCell->setColor(1.0f,0.0f,0.0f);
               break;
            }
            std::cout << "comp reached" << std::endl;
            // Generate successors and add to open list
            for (Cell* successor : getNeighbours(current)) {
                const bool is_in = closed.find(successor) != closed.end();
                if (is_in) {
                    std::cout << "(" << successor->x << ", " << successor->y << ")" << " is closed." << std::endl;
                    continue;
                }
                std::cout << "(" << successor->x << ", " << successor->y << ")" << " is NOT closed." << std::endl;
                // Compute f-score for successor
                successor->getNodeAddr()->g = current->getNodeAddr()->g + distance(current, successor);
                successor->getNodeAddr()->h = distance(successor, endCell);
                //FAULT IN ABOVE CODE.
                successor->getNodeAddr()->f = successor->getNodeAddr()->g + successor->getNodeAddr()->h;
                //current = successor;

                open.push(successor);
                //closed.insert(successor);
            }
        }
        if(open.empty()){
            std::cout << "open is empty" << std::endl;
            startCell->setColor(0.0f,1.0f,0.0f);
            std::cout << "end is at: " << "(" << endCell->x << ", " << endCell->y << ")" << std::endl; 
        }
}
std::priority_queue<Cell*, std::vector<Cell*>, NodeCompareA> * AStar::getPrio() {
    return &open;
}
std::set<Cell*>* AStar::getClosed() {
    std::set<Cell*>* closeptr = &closed;
    return closeptr;
}
std::vector<Cell*> AStar::reconstructPath(Cell* endNode) {
    
}

std::vector<Cell*> AStar::getNeighbours(Cell* cell) {
    std::cout << "Getting Neighbours" << std::endl;
    std::vector<Cell*> neighbours;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue;
            int checkX = cell->x + x;
            int checkY = cell->y + y;
            if (checkX >= 0 && checkX < Grid::GRID_WIDTH && checkY >= 0 && checkY < Grid::GRID_HEIGHT) {
                Cell* neighbour = &Grid::grid[checkX][checkY];
                if (!neighbour->isObstacle) {
                    std::cout << "Valid neighbour at: " << "(" << neighbour->x << ", " << neighbour->y << ")" << std::endl;
                    neighbours.push_back(neighbour);
                } else if (x != 0 && y != 0) {
                    // Diagonal neighbor is blocked, skip it
                    continue;
                }
            }
        }
    }
    return neighbours;
}
float AStar::distance(Cell* cell1, Cell* cell2) {
        return sqrtf(pow((cell2->x-cell1->x),2) + pow((cell2->y-cell1->y),2));
}
