#include <GL/glut.h>
#include <iostream>
using namespace std;

int xc, yc, radius;

void Plot(int x, int y) {
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2i(x, y);
    glEnd();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void drawcircle(int xc, int yc, int radius) {
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    Plot(xc + x, yc + y);
    Plot(xc - x, yc + y);
    Plot(xc + x, yc - y);
    Plot(xc - x, yc - y);
    Plot(xc + y, yc + x);
    Plot(xc - y, yc + x);
    Plot(xc + y, yc - x);
    Plot(xc - y, yc - x);

    while (x <= y) {
        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;

        // Plot all symmetric points in octants
        Plot(xc + x, yc + y);
        Plot(xc - x, yc + y);
        Plot(xc + x, yc - y);
        Plot(xc - x, yc - y);
        Plot(xc + y, yc + x);
        Plot(xc - y, yc + x);
        Plot(xc + y, yc - x);
        Plot(xc - y, yc - x);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawcircle(100,225,50);
    drawcircle(175,225,50);
    drawcircle(250,225,50);
    drawcircle(325,225,50);
    glFlush();
}

int main(int argc, char** argv) {


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("AUDI");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
