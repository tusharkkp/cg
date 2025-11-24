#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void ddaSemiCircle(int xc, int yc, int r, bool upperHalf) {
    float x = 0, y = r;
    float p = 1 - r;  // Decision parameter for circle

    while (x <= y) {
        // If upperHalf is true, draw the top half of the circle (positive y-values)
        if (upperHalf) {
            drawPixel(xc + x, yc + y); // First point (x, y)
            drawPixel(xc + y, yc + x); // Second point (y, x)
            drawPixel(xc - x, yc + y); // Third point (-x, y)
            drawPixel(xc - y, yc + x); // Fourth point (-y, x)
        }
        // If upperHalf is false, draw the lower half of the circle (negative y-values)
        else {
            drawPixel(xc + x, yc - y); // First point (x, -y)
            drawPixel(xc + y, yc - x); // Second point (y, -x)
            drawPixel(xc - x, yc - y); // Third point (-x, -y)
            drawPixel(xc - y, yc - x); // Fourth point (-y, -x)
        }

        x++;

        // Update y using the DDA algorithm
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the upper semi-circle with center at (250, 250) and radius 100
    ddaSemiCircle(250, 250, 100, true);

    // Draw the lower semi-circle with center at (250, 250) and radius 100
    //ddaSemiCircle(250, 250, 100, false);

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
    glutCreateWindow("DDA Semi-Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
