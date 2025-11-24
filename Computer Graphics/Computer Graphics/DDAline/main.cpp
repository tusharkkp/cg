#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x1_, y1_, x2_, y2_;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void DDA() {
    int dx = x2_ - x1_;
    int dy = y2_ - y1_;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1_;
    float y = y1_;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);

    for (int i = 0; i <= steps; i++) {
        drawPixel(round(x), round(y));
        x += xInc;
        y += yInc;}
    glFlush();
}
void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, 500, 0, 500);
}
int main(int argc, char **argv) {
    cout << "Enter (x1, y1, x2, y2): ";
    cin >> x1_ >> y1_ >> x2_ >> y2_;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Drawing Algorithm");
    init();
    glutDisplayFunc(DDA);
    glutMainLoop();
    return 0;
}
