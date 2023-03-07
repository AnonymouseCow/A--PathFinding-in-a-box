#ifndef CELL_H
#define CELL_H
#include "astarfinder.h"
class Cell;
struct Node {
    float f, g, h;
    float length;
    Cell* parent;
};
    class Cell {
    public:
        bool isObstacle; // True if the cell is an obstacle
        float color[3]; // RGB color of the cell
        float x, y; // X and Y position of the cell in world units
        Node node;
        Cell(bool isObstacle, float x, float y) : isObstacle(isObstacle), x(x), y(y) {
            node.parent = this;
            this->node.length = 1;
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
            std::cout << "comparing.." << std::endl;
            if(otherCell == nullptr) {
                std::cout << "null" << std::endl;
                return false;
            }
            return (otherCell->x == x && otherCell->y == y);
        }
        Node *getNodeAddr() {
            return &node;
        }
        double getf() const { return this->node.f; }
        void setColor(float r, float g, float b) {
            color[0] = r;
            color[1] = g;
            color[2] = b;
        }
        void setObstacle(bool value) {
            this->isObstacle = value;
            if(value) {
                //if we are an obstacle
                this->setColor(0.0f,0.0f,0.0f);
                //black
            } else {
                //if we aren't
                this->setColor(1.0f,1.0f,1.0f);
                //white
            }
        }
    };
#endif