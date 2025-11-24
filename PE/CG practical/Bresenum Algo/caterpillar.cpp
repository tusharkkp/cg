#include <GL/glut.h>

void setPixel(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void drawCircle(int xc, int yc, int r)
{
  int x = 0, y = r;
  int d = 3 - 2 * r;

  while (y >= x)
  {
    setPixel(xc + x, yc + y);
    setPixel(xc - x, yc + y);
    setPixel(xc + x, yc - y);
    setPixel(xc - x, yc - y);
    setPixel(xc + y, yc + x);
    setPixel(xc - y, yc + x);
    setPixel(xc + y, yc - x);
    setPixel(xc - y, yc - x);

    x++;
    if (d > 0)
    {
      y--;
      d = d + 4 * (x - y) + 10;
    }
    else
    {
      d = d + 4 * x + 6;
    }
  }
}

void drawCaterpillar()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0, 0, 0);
  drawCircle(100, 200, 50);

  glColor3f(0, 0, 0);
  drawCircle(170, 200, 50);

  glColor3f(1, 0, 0);
  drawCircle(240, 200, 50);
  drawCircle(310, 200, 50);
  drawCircle(380, 200, 50);

  glColor3f(0, 0, 0);
  glBegin(GL_LINES);
  glVertex2i(80, 250);
  glVertex2i(50, 300);

  glVertex2i(120, 250);
  glVertex2i(150, 300);
  glEnd();

  drawCircle(50, 300, 10);
  drawCircle(150, 300, 10);

  drawCircle(85, 215, 5);
  drawCircle(115, 215, 5);

  glFlush();
}

void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(2.0);
  gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Caterpillar using Bresenham's Circle Algorithm");
  init();
  glutDisplayFunc(drawCaterpillar);
  glutMainLoop();
  return 0;
}
