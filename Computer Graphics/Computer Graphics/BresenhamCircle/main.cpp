#include <GL/glut.h>
#include <iostream>
using namespace std;

int xc, yc, r;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}
void bresenhamCircle() {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    while (x <= y) {
        drawPixel(x, y);
        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glFlush();
}
void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, 500, 0, 500);
}
int main(int argc, char **argv) {
    cout << "Enter center (xc, yc) and radius: ";
    cin >> xc >> yc >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Circle Drawing Algorithm");
    init();
    glutDisplayFunc(bresenhamCircle);
    glutMainLoop();
    return 0;
}
