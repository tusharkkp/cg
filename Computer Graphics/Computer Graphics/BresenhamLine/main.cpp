#include <GL/glut.h>
#include <iostream>
using namespace std;

int x1_, y1_, x2_, y2_;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void bresenhamLine() {
    int dx = abs(x2_ - x1_);
    int dy = abs(y2_ - y1_);
    int p = 2 * dy - dx;
    int x, y;

    if (x1_ > x2_) {
        x = x2_;
        y = y2_;
        x2_ = x1_;
    } else {
        x = x1_;
        y = y1_;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawPixel(x, y);

    while (x < x2_) {
        x++;
        if (p < 0)
            p += 2 * dy;
        else {
            y++;
            p += 2 * (dy - dx);
        }
        drawPixel(x, y);
    }
    glFlush();
}
void init() {
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv) {
    cout << "Enter (x1, y1, x2, y2): ";
    cin >> x1_ >> y1_ >> x2_ >> y2_;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Line Drawing Algorithm");
    init();
    glutDisplayFunc(bresenhamLine);
    glutMainLoop();
    return 0;
}
