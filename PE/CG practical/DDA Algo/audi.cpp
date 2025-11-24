#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

void drawPixel(int x, int y) {
    glColor3f(1.0f, 1.0f, 1.0f);  // White color
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing the four interlocking circles (Audi logo)
    ddaCircle(100, 225, 50);  // First circle (centered at (100, 225), radius 50)
    ddaCircle(175, 225, 50);  // Second circle (centered at (175, 225), radius 50)
    ddaCircle(250, 225, 50);  // Third circle (centered at (250, 225), radius 50)
    ddaCircle(325, 225, 50);  // Fourth circle (centered at (325, 225), radius 50)

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
    glutCreateWindow("Audi Logo using DDA Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
