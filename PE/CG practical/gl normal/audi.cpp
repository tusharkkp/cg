#include <GL/glut.h>
#include <math.h>

void drawCircle(float x, float y, float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(100); // 360 degrees in radians
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void displayAudiLogo(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color to white for the rings
    glColor3f(1.0, 1.0, 1.0);

    // Draw the four interlocked rings
    float radius = 0.3f;
    float distance = radius * 1.6f; // Distance between centers to create overlap

    drawCircle(-distance, 0.0f, radius);  // Leftmost ring
    drawCircle(0.0f, 0.0f, radius);       // Left-center ring
    drawCircle(distance, 0.0f, radius);   // Right-center ring
    drawCircle(2 * distance, 0.0f, radius); // Rightmost ring

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Audi Logo");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background to black
    gluOrtho2D(-2.0, 2.0, -1.0, 1.0);     // Set the coordinate system
    glutDisplayFunc(displayAudiLogo);
    glutMainLoop();
    return 0;
}
