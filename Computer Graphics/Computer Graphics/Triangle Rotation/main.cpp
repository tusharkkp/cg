#include <GL/glut.h>

float angleX = 0.0, angleY = 0.0, angleZ = 0.0;
int axis = 2; // Default Z-axis rotation
float speed = 0.15f; // Slow and smooth

void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.8, 0.9); // Pastel Pink
    glVertex3f(0.0, 0.6, 0.0);
    glColor3f(0.8, 1.0, 0.8); // Pastel Green
    glVertex3f(-0.6, -0.4, 0.0);
    glColor3f(0.8, 0.9, 1.0); // Pastel Blue
    glVertex3f(0.6, -0.4, 0.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);
    drawTriangle();
    glutSwapBuffers();
}

void idle() {
    if (axis == 0) angleX += speed;
    else if (axis == 1) angleY += speed;
    else angleZ += speed;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) axis = 0;
        else if (button == GLUT_RIGHT_BUTTON) axis = 1;
        else if (button == GLUT_MIDDLE_BUTTON) axis = 2;
    }
}

void init() {
    glClearColor(0.95, 0.95, 0.95, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Pastel Rotating Triangle");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
