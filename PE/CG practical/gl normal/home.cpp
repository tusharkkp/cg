#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the house base (square)
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.4f, 0.2f); // Brown color
    glVertex2f(-0.4f, -0.4f);    // Bottom-left corner
    glVertex2f(0.4f, -0.4f);     // Bottom-right corner
    glVertex2f(0.4f, 0.2f);      // Top-right corner
    glVertex2f(-0.4f, 0.2f);     // Top-left corner
    glEnd();

    // Draw the roof (triangle)
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.1f, 0.1f); // Red color
    glVertex2f(-0.5f, 0.2f);     // Left corner
    glVertex2f(0.5f, 0.2f);      // Right corner
    glVertex2f(0.0f, 0.6f);      // Top corner
    glEnd();

    // Draw the door (rectangle)
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.2f, 0.1f); // Dark brown color
    glVertex2f(-0.1f, -0.4f);    // Bottom-left corner
    glVertex2f(0.1f, -0.4f);     // Bottom-right corner
    glVertex2f(0.1f, 0.0f);      // Top-right corner
    glVertex2f(-0.1f, 0.0f);     // Top-left corner
    glEnd();

    // Draw the window (square)
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.5f, 0.9f); // Blue color
    glVertex2f(-0.3f, 0.0f);     // Bottom-left corner
    glVertex2f(-0.1f, 0.0f);     // Bottom-right corner
    glVertex2f(-0.1f, 0.2f);     // Top-right corner
    glVertex2f(-0.3f, 0.2f);     // Top-left corner
    glEnd();

    // Draw the chimney
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.0f, 0.0f); // Dark red color
    glVertex2f(0.2f, 0.4f);      // Bottom-left corner
    glVertex2f(0.3f, 0.4f);      // Bottom-right corner
    glVertex2f(0.3f, 0.6f);      // Top-right corner
    glVertex2f(0.2f, 0.6f);      // Top-left corner
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("House in OpenGL");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
