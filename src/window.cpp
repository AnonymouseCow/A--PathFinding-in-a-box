#include "cell.h"
#include "grid.h"
#include "astar.h"
#include <iostream>
void display();
void reshape(int,int);
void init()
{
    glClearColor(0.0,0.0,0.0,1.0);

}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    AStar A;
    // Center grid in window
    glTranslatef(-Grid::GRID_WIDTH / 2.0f, -Grid::GRID_HEIGHT / 2.0f, 0.0f);
    
    // Draw grid
    
    Grid::buildGrid(&A);
    A.findPath(&Grid::grid[0][0],&Grid::grid[50][50]);
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    std::cout.flush();
    std::cout << "started" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Grid of Cells");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void reshape(int width, int height) {
    // Maintain aspect ratio of grid
    float aspect = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect > 1.0f) {
        gluOrtho2D(-Grid::GRID_WIDTH / 2.0f * aspect, Grid::GRID_WIDTH / 2.0f * aspect, -Grid::GRID_HEIGHT / 2.0f, Grid::GRID_HEIGHT / 2.0f);
    } else {
        gluOrtho2D(-Grid::GRID_WIDTH / 2.0f, Grid::GRID_WIDTH / 2.0f, -Grid::GRID_HEIGHT / 2.0f / aspect, Grid::GRID_HEIGHT / 2.0f / aspect);
    }
    glMatrixMode(GL_MODELVIEW);
}