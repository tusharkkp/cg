#include <GL/glut.h>
#include <iostream>
using namespace std;

int xc, yc, r;

void plot(int x, int y) {
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
void DDACircle() {
    glClear(GL_COLOR_BUFFER_BIT);
    int x = 0, y = r;

    while (x <= y) {
        plot(x, y);
        x++;
        int tempY = y;
        while (tempY * tempY > r * r - x * x)
            tempY--;
        y = tempY;
    }
    glFlush();
}
void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, 500, 0, 500);
}
int main(int argc, char** argv) {
    cout << "Enter center (xc, yc) and radius: ";
    cin >> xc >> yc >> r;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Circle Algorithm");
    init();
    glutDisplayFunc(DDACircle);
    glutMainLoop();
    return 0;
}
