#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Function to draw a single pixel at (x, y)
void drawpixel(int x, int y) {
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color for the star
    glVertex2i(x, y);
    glEnd();
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Set up the coordinate system
}

// Bresenham's line drawing algorithm
void drawline(int x1, int y1, int x2, int y2) {
    int dx, dy, i, e;
    int incx = 1, incy = 1, inc1, inc2;
    int x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    if (x2 < x1) incx = -1;
    if (y2 < y1) incy = -1;

    x = x1;
    y = y1;

    if (dx > dy) {
        drawpixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;

        for (i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += inc1;
            } else {
                e += inc2;
            }
            x += incx;
            drawpixel(x, y);
        }
    } else {
        drawpixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;

        for (i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            } else {
                e += inc2;
            }
            y += incy;
            drawpixel(x, y);
        }
    }
}

// Function to draw a star by drawing two overlapping equilateral triangles
void drawStar(int centerX, int centerY, int size) {
    float angle = M_PI / 3;  // 60 degrees in radians for an equilateral triangle
    int halfSize = size / 2;

    // Coordinates for the first triangle pointing upwards
    int x1 = centerX;
    int y1 = centerY + size;

    int x2 = centerX - static_cast<int>(size * sin(angle));
    int y2 = centerY - halfSize;

    int x3 = centerX + static_cast<int>(size * sin(angle));
    int y3 = centerY - halfSize;

    // Draw the first triangle
    drawline(x1, y1, x2, y2);
    drawline(x2, y2, x3, y3);
    drawline(x3, y3, x1, y1);

    // Coordinates for the second triangle pointing downwards
    int x4 = centerX;
    int y4 = centerY - size;

    int x5 = centerX - static_cast<int>(size * sin(angle));
    int y5 = centerY + halfSize;

    int x6 = centerX + static_cast<int>(size * sin(angle));
    int y6 = centerY + halfSize;

    // Draw the second triangle
    drawline(x4, y4, x5, y5);
    drawline(x5, y5, x6, y6);
    drawline(x6, y6, x4, y4);
}

// Display function to draw the star
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int centerX = 250;  // Center of the window
    int centerY = 250;
    int size = 100;  // Size of the star

    // Draw the star at the specified location
    drawStar(centerX, centerY, size);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Star Drawing with Two Overlapping Triangles");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
