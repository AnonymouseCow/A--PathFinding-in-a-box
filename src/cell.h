#ifndef CELL_H
#define CELL_H
#include "astarfinder.h"
class Cell;
struct Node {
    int x, y;
    float f, g, h;
    Cell* parent;
};
    class Cell {
    public:
        bool isObstacle; // True if the cell is an obstacle
        float color[3]; // RGB color of the cell
        float x, y; // X and Y position of the cell in world units
        Node node;
        Cell(bool isObstacle, float x, float y) : isObstacle(isObstacle), x(x), y(y) {
            node.x = x;
            node.y = y;
            node.parent = this;
            if(!isObstacle){
            color[0] = 1.0f; // Set default color to white
            color[1] = 1.0f;
            color[2] = 1.0f;
            } else {
            color[0] = 0.0f; // Set default color to black
            color[1] = 0.0f;
            color[2] = 0.0f;
            }
        }
        bool compareCells(Cell* otherCell) {
            if(x == otherCell->x) {
                if(y == otherCell->y) {
                    return true;
                }
            }
            return false;
        }
        Node *getNodeAddr() {
            Node *nodeaddr = &node;
            return nodeaddr;
        }
        void setColor(float r, float g, float b) {
            color[0] = r;
            color[1] = g;
            color[2] = b;
            glutPostRedisplay();
        }
    };
#endif