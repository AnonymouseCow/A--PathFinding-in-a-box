#ifndef ASTAR_H
#define ASTAR_H

#include "cell.h"
#include <queue>
#include <set>
#include "nodecomp.h"
class AStar {
public:
    AStar();
    void findPath(Cell* startCell, Cell* endCell);
    std::priority_queue<Node*, std::vector<Node*>, NodeCompareA>* getPrio();
    std::set<Node*>* getClosed();
private:

    static std::priority_queue<Node*, std::vector<Node*>, NodeCompareA> open;
    static std::set<Node*> closed;
    std::vector<Node*> reconstructPath(Node* endNode);
    std::vector<Node*> getNeighbours(Node* node);
    float distance(Node* node1, Node* node2);
    bool isObstacle(Node* node);
    bool inBounds(Node* node);
};

#endif // ASTAR_H
