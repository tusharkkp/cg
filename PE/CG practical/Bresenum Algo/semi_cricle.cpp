#include <GL/glut.h>

void drawSemiCircle(int Xc, int Yc, int R)
{
    int X = 0;
    int Y = R;
    int P = 3 - 2 * R;

    glBegin(GL_POINTS);

    // Draw points only in the upper half of the circle (Y >= 0)
    while (X <= Y)
    {
        // Plot the points for the upper semi-circle
        glVertex2i(Xc + X, Yc + Y);
        glVertex2i(Xc - X, Yc + Y);
        glVertex2i(Xc + Y, Yc + X);
        glVertex2i(Xc - Y, Yc + X);

        if (P < 0)
        {
            P = P + 4 * X + 6;
        }
        else
        {
            P = P + 4 * (X - Y) + 10;
            Y--;
        }
        X++;

        if (X == Y)
            break;
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int Xc = 200, Yc = 200, R = 100;
    drawSemiCircle(Xc, Yc, R); // Call to draw the semi-circle
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Semi-Circle Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
