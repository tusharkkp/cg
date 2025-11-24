#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

void drawPixel(int x, int y) {
    glColor3f(1.0f, 0, 0);  // Red color
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void ddaCircle(int xc, int yc, int r) {
    float x = r, y = 0;
    float p = 1 - r;  // Decision parameter

    // Initial point
    drawPixel(xc + x, yc + y);

    // Circle symmetry points
    while (x > y) {
        y++;

        // Update decision parameter
        if (p <= 0) {
            p = p + 2 * y + 1;
        } else {
            x--;
            p = p + 2 * (y - x) + 1;
        }

        // Plot all 8 octants
        drawPixel(xc + x, yc + y);   // 1st octant
        drawPixel(xc - x, yc + y);   // 2nd octant
        drawPixel(xc + x, yc - y);   // 3rd octant
        drawPixel(xc - x, yc - y);   // 4th octant
        drawPixel(xc + y, yc + x);   // 5th octant
        drawPixel(xc - y, yc + x);   // 6th octant
        drawPixel(xc + y, yc - x);   // 7th octant
        drawPixel(xc - y, yc - x);   // 8th octant
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Coordinate system
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    ddaCircle(250, 250, 100);  // Draw a circle with center (250, 250) and radius 100
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
