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
    std::priority_queue<Cell*, std::vector<Cell*>, NodeCompareA>* getPrio();
    std::set<Cell*>* getClosed();
private:

    static std::priority_queue<Cell*, std::vector<Cell*>, NodeCompareA> open;
    static std::set<Cell*> closed;
    std::vector<Cell*> reconstructPath(Cell* cell);
    std::vector<Cell*> getNeighbours(Cell* cell);
    float distance(Cell* cell1, Cell* cell2);
};

#endif // ASTAR_H
