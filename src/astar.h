#ifndef ASTAR_H
#define ASTAR_H

#include "grid.h"
#include "cell.h"

class AStar {
public:
    AStar();
    std::vector<Node*> findPath(Cell& startCell, Cell& endCell);
private:
    std::vector<Node*> reconstructPath(Node* endNode);
    std::vector<Node*> getNeighbours(Node* node);
    float distance(Node* node1, Node* node2);
    bool isObstacle(Node* node);
    bool inBounds(Node* node);
};

#endif // ASTAR_H
