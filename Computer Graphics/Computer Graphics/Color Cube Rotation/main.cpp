#include <GL/glut.h>

float angleX = 0.0, angleY = 0.0, angleZ = 0.0;
int axis = 0; // 0=X, 1=Y, 2=Z
float speed = 0.1f; // Slow rotation speed

void drawCube() {
    glBegin(GL_QUADS);
    // Front face (Pastel Pink)
    glColor3f(1.0, 0.8, 0.8);
    glVertex3f(-0.5, -0.5,  0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f(-0.5,  0.5,  0.5);

    // Back face (Pastel Blue)
    glColor3f(0.8, 0.8, 1.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f( 0.5,  0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);

    // Top face (Pastel Green)
    glColor3f(0.8, 1.0, 0.8);
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5, -0.5);

    // Bottom face (Pastel Yellow)
    glColor3f(1.0, 1.0, 0.8);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f(-0.5, -0.5,  0.5);

    // Right face (Pastel Purple)
    glColor3f(0.9, 0.8, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5,  0.5, -0.5);
    glVertex3f(0.5,  0.5,  0.5);
    glVertex3f(0.5, -0.5,  0.5);

    // Left face (Pastel Orange)
    glColor3f(1.0, 0.9, 0.8);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5,  0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f(-0.5,  0.5, -0.5);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);
    drawCube();
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
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.95, 0.95, 0.95, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Pastel Rotating Cube");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
