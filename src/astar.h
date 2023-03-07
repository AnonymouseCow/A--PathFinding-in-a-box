#ifndef ASTAR_H
#define ASTAR_H

#include "cell.h"
#include <queue>
#include <set>
#include "nodecomp.h"
template<class PQ>
class Extractable : public PQ {
public:
    using PQ::PQ;
    using typename PQ::container_type;
    container_type&& container() && { return std::move(this->c); }
    const container_type& container() const & { return this->c; }
    container_type& container() & { return this->c; }

    container_type sorted_container() && {
        std::sort_heap(this->c.begin(), this->c.end(), this->comp);
        return std::move(this->c);
    }
};
class AStar {
public:
    AStar();
    void findPath(Cell* startCell, Cell* endCell);
    Extractable<std::priority_queue<Cell*, std::vector<Cell*>, NodeCompareA>>* getPrio();
    std::set<Cell*>* getClosed();
private:

    static Extractable<std::priority_queue<Cell*, std::vector<Cell*>, NodeCompareA>> open;
    static std::set<Cell*> closed;
    std::vector<Cell*> reconstructPath(Cell* cell);
    std::vector<Cell*> getNeighbours(Cell* cell, Cell* endCell);
    float distance(Cell* cell1, Cell* cell2);
};

#endif // ASTAR_H
