
#include "astarfinder.h"
#include "grid.h"
#include <math.h>
#include <queue>
#include <set>
#include <iostream>
#include <unistd.h>
Extractable<std::priority_queue<Cell*, std::vector<Cell*>, NodeCompareA>> AStar::open;
std::set<Cell*> AStar::closed;
AStar::AStar() {}
void AStar::findPath(Cell* startCell, Cell* endCell) {
    // Add start node to open list
        std::cout << "Beginning pathfinding..";
        std::cout << "START AT: " << " (" << startCell->x << ", " << startCell->y << ")" << std::endl; 
        endCell->setColor(0.0f,0.0f,1.0f);
        open.push(startCell);
        Cell* current = nullptr;
        while (!open.empty()) {
            //usleep(200000);
            current = open.top();
            std::cout << "Picking (" << current->x << ", " << current->y << ") Recalculated F: " << current->getNodeAddr()->f << std::endl;  
            current->setColor(1.0f,0.0f,0.0f);
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
            for (Cell* successor : getNeighbours(current, endCell)) {
                std::cout << "(" << successor->x << ", " << successor->y << ")" << " is NOT closed." << std::endl;
                // Compute f-score for successor
                successor->getNodeAddr()->g = current->getNodeAddr()->g + distance(current, successor);
                successor->getNodeAddr()->h = distance(successor, endCell);
                successor->getNodeAddr()->f = successor->getNodeAddr()->g + successor->getNodeAddr()->h;
                //std::vector<Cell*> res = std::move(open).container();
                const bool is_in = closed.find(successor) != closed.end();
                if (is_in) {
                    std::cout << " [CLOSED] " << "Valid neighbour at: " << "(" << successor->x << ", " << successor->y << ") F:" << successor->getNodeAddr()->f << std::endl;
                    successor->setColor(.415f,.4256f,.641f);
                    continue;
                }
                successor->setColor(1.0f,.4f,0.0f);
                std::cout << " [OPEN]   " << "Valid neighbour at: " << "(" << successor->x << ", " << successor->y << ") F:" << successor->getNodeAddr()->f << std::endl;
                // Compute f-score for successor       
                //current = successor;
                open.push(successor);
                closed.insert(successor);
            }
        }
        closed.insert(current);
        if(open.empty()){
            startCell->setColor(0.0f,1.0f,0.0f);
            std::cout << "end is at: " << "(" << endCell->x << ", " << endCell->y << ")" << std::endl; 
        }
}
Extractable<std::priority_queue<Cell*, std::vector<Cell*>, NodeCompareA>>* AStar::getPrio() {
    return &open;
}
std::set<Cell*>* AStar::getClosed() {
    std::set<Cell*>* closeptr = &closed;
    return closeptr;
}
std::vector<Cell*> AStar::reconstructPath(Cell* endNode) {
    
}

std::vector<Cell*> AStar::getNeighbours(Cell* cell, Cell* endCell) {
    //Check if the cell is available and not closed here.
    std::cout << "Getting Neighbours" << std::endl;
    std::vector<Cell*> neighbours;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue;
            int checkX = cell->x + x;
            int checkY = cell->y + y;
            if (checkX >= 0 && checkX < Grid::GRID_SIZE && checkY >= 0 && checkY < Grid::GRID_SIZE) {
                Cell* neighbour = &Grid::grid[checkX][checkY];
                const bool isEnd = endCell->compareCells(cell);
                if (!neighbour->isObstacle && isEnd) {
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
    
        float NL1 = cell1->getNodeAddr()->length;
        float NL2 = cell2->getNodeAddr()->length;
        double dx = abs(cell1->x - cell2->x);
        double dy = abs(cell1->y - cell2->y);
        return (NL1*NL2) * (dx + dy) + (sqrt(2)-2*(NL1*NL2)) * std::min(dx,dy);
}
