#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void ddaLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    float xIncrement, yIncrement, x = x1, y = y1;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    xIncrement = dx / float(steps);
    yIncrement = dy / float(steps);

    for (int i = 0; i <= steps; i++) {
        drawPixel(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
}

void drawSquare(int x1, int y1, int sideLength) {
    ddaLine(x1, y1, x1 + sideLength, y1);                // Bottom side
    ddaLine(x1 + sideLength, y1, x1 + sideLength, y1 + sideLength); // Right side
    ddaLine(x1 + sideLength, y1 + sideLength, x1, y1 + sideLength); // Top side
    ddaLine(x1, y1 + sideLength, x1, y1);                // Left side
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    ddaLine(x1, y1, x2, y2);  // Side 1
    ddaLine(x2, y2, x3, y3);  // Side 2
    ddaLine(x3, y3, x1, y1);  // Side 3
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing a line from (50, 50) to (200, 200)
    ddaLine(50, 50, 200, 200);

    // Drawing a square with bottom-left corner at (100, 100) and side length 100
    drawSquare(100, 100, 100);

    // Drawing a triangle with vertices at (300, 300), (400, 300), and (350, 400)
    drawTriangle(300, 300, 400, 300, 350, 400);

    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line, Square, and Triangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
