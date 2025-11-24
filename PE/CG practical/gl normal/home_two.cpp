#include <GL/glut.h>

void displayHome(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color to brown for the house
    glColor3f(0.6, 0.3, 0.0);

    // Draw the main rectangle for the house
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.0);
    glVertex2f(-0.5, 0.0);
    glEnd();

    // Set the color to dark red for the roof
    glColor3f(0.7, 0.0, 0.0);

    // Draw the roof as a triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6, 0.0);
    glVertex2f(0.6, 0.0);
    glVertex2f(0.0, 0.5);
    glEnd();

    // Set the color to blue for the door
    glColor3f(0.0, 0.0, 1.0);

    // Draw the door as a smaller rectangle
    glBegin(GL_POLYGON);
    glVertex2f(-0.1, -0.5);
    glVertex2f(0.1, -0.5);
    glVertex2f(0.1, -0.2);
    glVertex2f(-0.1, -0.2);
    glEnd();

    // Set the color to light blue for the windows
    glColor3f(0.7, 0.9, 1.0);

    // Draw the first window as a smaller rectangle
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, -0.2);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.2, -0.1);
    glVertex2f(-0.4, -0.1);
    glEnd();

    // Draw the second window as a smaller rectangle
    glBegin(GL_POLYGON);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.4, -0.2);
    glVertex2f(0.4, -0.1);
    glVertex2f(0.2, -0.1);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Home with Windows");
    glutDisplayFunc(displayHome);
    glutMainLoop();
    return 0;
}
