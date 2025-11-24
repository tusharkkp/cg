#include <GL/glut.h>
#include <iostream>
using namespace std;
int x1, x2, y1, y2;

void drawpixel(int x, int y) {
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(x, y);
    glEnd();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void drawline(int x1, int x2, int y1, int y2) {
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawline(150,150,120,150);
    drawline(150,120,150,150);
    drawline(120,120,150,170);
    drawline(120,150,170,170);
    drawline(150,150,170,200);
    drawline(150,170,200,200);
    drawline(170,170,200,170);
    drawline(170,200,170,170);
    drawline(200,200,170,150);
    drawline(200,170,150,150);
    drawline(170,170,150,120);
    drawline(170,150,120,120);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Home");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
