#include <GL/glut.h>
#include <cmath>
#include <iostream>

void ddaLine(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps, Xinc, Yinc;
    float x = x1, y = y1;
    if (fabs(dx) > fabs(dy))
    {
        steps = fabs(dx);
    }
    else
    {
        steps = fabs(dy);
    }
    Xinc = dx / steps;
    Yinc = dy / steps;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(round(x), round(y));
        x += Xinc;
        y += Yinc;
    }
    glEnd();
}

void drawHouse()
{
    // Base of the house - red
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    ddaLine(100, 100, 300, 100);
    ddaLine(300, 100, 300, 300);
    ddaLine(300, 300, 100, 300);
    ddaLine(100, 300, 100, 100);

    // Roof - green
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    ddaLine(100, 300, 200, 400);
    ddaLine(300, 300, 200, 400);

    // Door - blue
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    ddaLine(175, 100, 175, 150);
    ddaLine(225, 100, 225, 150);
    ddaLine(175, 150, 225, 150);

    // Left window - cyan
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    ddaLine(125, 200, 175, 200);
    ddaLine(125, 200, 125, 250);
    ddaLine(175, 200, 175, 250);
    ddaLine(125, 250, 175, 250);

    // Right window - yellow
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    ddaLine(225, 200, 275, 200);
    ddaLine(225, 200, 225, 250);
    ddaLine(275, 200, 275, 250);
    ddaLine(225, 250, 275, 250);
}

void initOpenGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawHouse();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("House using DDA Line Drawing Algorithm");
    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
