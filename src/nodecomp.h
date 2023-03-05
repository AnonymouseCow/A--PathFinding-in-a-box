#include "cell.h"
struct NodeCompare {
    bool operator()(const Node& a, const Node& b) const {
        // Compare nodes by their f-score
        return a.f > b.f;
    }
};
struct NodeCompareA {
    bool operator()(const Node* a, const Node* b) const {
        // Compare nodes by their f-score
        return a->f > b->f;
    }
};
