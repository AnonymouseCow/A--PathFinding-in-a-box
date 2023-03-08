#include "cell.h"
#include "grid.h"
#include "astar.h"
#include "window.h"
#define _GLIBCXX_USE_NANOSLEEP
#define MB_LEFT   0
#define MB_MIDDLE 1
#define MB_RIGHT  2
#define LMB_PRESSED (1<<0)
#define MMB_PRESSED (1<<1)
#define RMB_PRESSED (1<<2)
#define LMB_CLICKED (1<<16)
#define MMB_CLICKED (1<<17)
#define RMB_CLICKED (1<<18)
#define MB_PRESSED(state, button) (1<<(button))
#define MB_CLICKED(state, button) (1<<((button)+16))
#define MB_MASK_PRESSED 0x0000ffffL
#define MB_MASK_CLICKED 0xffff0000L
uint32_t mouse_status = 0;
int g_width;
int g_height;
float g_aspect;
AStar A;
bool g_mousedown;
std::pair<int*,int*> mouseCoords;
GLuint gFramesPerSecond;
void FPS(void) {
  static GLint Frames = 0;         // frames averaged over 1000mS
  static GLuint Clock;             // [milliSeconds]
  static GLuint PreviousClock = 0; // [milliSeconds]
  static GLuint NextClock = 0;     // [milliSeconds]

  ++Frames;
  Clock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
  if ( Clock < NextClock ) return;

  gFramesPerSecond = Frames/1; // store the averaged number of frames per second

  PreviousClock = Clock;
  NextClock = Clock+1000; // 1000mS=1S in the future
  Frames=0;
}
void timer(int value)
{
  const int desiredFPS=120;
  glutTimerFunc(1000/desiredFPS, timer, ++value);

  //put your specific idle code here
  //... this code will run at desiredFPS
  //end your specific idle code here

  FPS(); //only call once per frame loop to measure FPS 
  glutPostRedisplay();
}
void display();
void reshape(int,int);
void handleMouse(int,int,int,int);
void handleDrag(int,int);
void keyboardHandler(unsigned char,int,int);

void startLoops(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutCreateWindow("2D Grid of Cells");
    glutTimerFunc(0,timer,0);
    glutMotionFunc(handleDrag);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardHandler);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouse);
    glutMainLoop();
}
std::pair<int, int> pixelToGridCoords(int x, int y) {
    int gridX = x / (double) g_width
           * (Grid::GRID_SIZE - 0) + 0;
    int gridY = (1 - y / (double) g_height)
           * (Grid::GRID_SIZE - 0) + 0;
    return std::make_pair(gridX,gridY);
}
void init()
{
    glClearColor(0.0,0.0,0.0,0.5);

}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Center grid in window
    glTranslatef(-Grid::GRID_WIDTH / 2.0f, -Grid::GRID_HEIGHT / 2.0f, 0.0f);
    
    // Draw grid
    Grid::drawGrid();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    //std::thread bt(task, 500);
    std::cout.flush();
    std::cout << "started" << std::endl;
    Grid::buildGrid();
    startLoops(argc, argv);
    return 0;
}

void reshape(int width, int height) {
    // Maintain aspect ratio of grid
    g_width = width;
    g_height = height;
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
void handleMouse(int button, int state, int x, int y) {
    int gridX;
    int gridY;
    std::tie(gridX, gridY) = pixelToGridCoords(x, y);
    int b;
    switch(button) {
    case GLUT_LEFT_BUTTON:   b=MB_LEFT;   break;
    case GLUT_MIDDLE_BUTTON: b=MB_MIDDLE; break;
    case GLUT_RIGHT_BUTTON:  b=MB_RIGHT;  break;
    }
    bool isUp = (GLUT_UP == state);
    switch(b) {
        case MB_LEFT:
            if(!isUp) {
                std::cout << "LEFT MB PRESSED: " << "(" << gridX << ", " << gridY<< ")" << std::endl;
                mouseCoords = std::make_pair(&gridX, &gridY);
                Grid::grid[gridX][gridY].setObstacle(true);
                g_mousedown = true;
            }  else {
                g_mousedown = false;
            }
        break;
        case MB_RIGHT:
            if(!isUp) {
                Grid::grid[gridX][gridY].setObstacle(false);
                std::cout << "RIGHT MB PRESSED: " << "(" << gridX << ", " << gridY<< ")" << std::endl;

            } 
        break;
    }
}
void keyboardHandler(unsigned char key, int x, int y) {
    std::cout << "keypress" << std::endl;
    switch (key) 
    {    
       case 113: 
       A.findPath(&Grid::grid[0][0], &Grid::grid[49][49]); 
       break;
    }
}
void handleDrag(int x, int y) {
    std::cout << "Dragging!" << std::endl;
    int gridX;
    int gridY;
    std::tie(gridX, gridY) = pixelToGridCoords(x, y);
    if(g_mousedown) {
        Grid::grid[gridX][gridY].setObstacle(true);
    }
}