#include "astar.h"
#include "astarfinder.h"
#include "cell.h"
#include <queue>
#include <set>
struct NodeCompare {
    bool operator()(const Node& a, const Node& b) const {
        // Compare nodes by their f-score
        return a.f > b.f;
    }
};

AStar::AStar() {}
std::vector<Node*> AStar::findPath(Cell& startCell, Cell& endCell) {
    // Add start node to open list
    std::priority_queue<Node, std::vector<Node>, NodeCompare >open;
    std::set<Node*> closed;
        open.push(startCell.node);

        while (!open.empty()) {
            Node current = open.top();
            open.pop();

            if (endCell.compareCells(*current.parent)) {
                // Found goal, do something with path

                break;
            }

            // Generate successors and add to open list
            for (Node *successor : getNeighbours(&current)) {
                if (closed.count(successor) > 0) {
                    // Successor already visited
                    continue;
                }

                // Compute f-score for successor
                successor->g = current.g + distance(&current, successor);
                successor->h = distance(successor, endCell.getNodeAddr());
                successor->f = successor->g + successor->h;

                open.push(*successor);
                closed.insert(successor);
                
            }
        }
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
    // Distance calculation implementation goes here
}

bool AStar::isObstacle(Node* node) {
    // Obstacle detection implementation goes here
}

bool AStar::inBounds(Node* node) {
    // Bounds checking implementation goes here
}