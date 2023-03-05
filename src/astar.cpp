
#include "astarfinder.h"
#include "grid.h"
#include <math.h>
#include <queue>
#include <set>
#include <iostream>
std::priority_queue<Node*, std::vector<Node*>, NodeCompareA> AStar::open;
std::set<Node*> AStar::closed;
AStar::AStar() {}
void AStar::findPath(Cell* startCell, Cell* endCell) {
    // Add start node to open list
        open.push(startCell->getNodeAddr());

        while (!open.empty()) {
            Node* current = open.top();
            open.pop();
            std::cout << "open not empty" << std::endl;
            std::cout << "Current Coords: (" << current->x <<", " << current->y << ")" << std::endl;
            if (endCell->compareCells(current->parent)) {
                std::cout << "found the end";
                endCell->setColor(1.0f,0.0f,0.0f);
                break;
            }

            // Generate successors and add to open list
            for (Node *successor : getNeighbours(current)) {
                if (closed.count(successor) > 0) {
                    // Successor already visited
                    continue;
                }

                // Compute f-score for successor
                successor->g = current->g + distance(current, successor);
                successor->h = distance(successor, endCell->getNodeAddr());
                successor->f = successor->g + successor->h;

                open.push(successor);
                closed.insert(successor);
                
            }
        }
        if(open.empty()){
            std::cout << "open is empty" << std::endl;
            std::cout << "end is at: " << "(" << endCell->x << ", " << endCell->y << ")" << std::endl; 
        }
}
std::priority_queue<Node*, std::vector<Node*>, NodeCompareA> * AStar::getPrio() {
    std::priority_queue<Node*, std::vector<Node*>, NodeCompareA>* prioptr = &open;
    return prioptr;
}
std::set<Node*>* AStar::getClosed() {
    std::set<Node*>* closeptr = &closed;
    return closeptr;
}
std::vector<Node*> AStar::reconstructPath(Node* endNode) {
    // Path reconstruction implementation goes here
}

std::vector<Node*> AStar::getNeighbours(Node* node) {
    std::vector<Node*> neighbours;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue;
            int checkX = node->x + x;
            int checkY = node->y + y;
            if (checkX >= 0 && checkX < Grid::GRID_WIDTH && checkY >= 0 && checkY < Grid::GRID_HEIGHT) {
                neighbours.push_back(Grid::grid[checkX][checkY].getNodeAddr());
            }
        }
    }
    return neighbours;
}

float AStar::distance(Node* node1, Node* node2) {
        return sqrtf(pow((node2->x-node1->x),2) + pow((node2->y-node1->y),2));
}

bool AStar::isObstacle(Node* node) {
    //Is this even necessary??
}

bool AStar::inBounds(Node* node) {
    // Bounds checking implementation goes here
}