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
void midpointCircle() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    int x = 0, y = r;
    float p = 1 - r;
    while (x <= y) {
        drawPixel(x, y);
        x++;
        if (p < 0) p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;}}
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
    glutCreateWindow("Midpoint Circle Drawing Algorithm");
    init();
    glutDisplayFunc(midpointCircle);
    glutMainLoop();
    return 0;
}
