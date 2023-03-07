#include "cell.h"
struct NodeCompare {
    bool operator()(const Node& a, const Node& b) const {
        // Compare nodes by their f-score
        return a.f > b.f;
    }
};
struct NodeCompareA {
    bool operator()(const Cell* a, const Cell* b) const {
        const double aF = a->getf();
        const double bF = b->getf();
        // Compare nodes by their f-score
        return aF > bF;
    }
};
