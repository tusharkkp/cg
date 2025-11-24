#include <GL/glut.h>
#include <math.h>

GLfloat d = 0;

void MyInit() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void Spin() {
    d = d + 0.02;
    if (d > 360) d = 0;
    glutPostRedisplay();
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) {
    glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
    glEnd();
}

void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[]) {
    glColor3f(1, 0, 0);
    Face(V0, V1, V2, V3); // Front Face
    glColor3f(0, 1, 0);
    Face(V4, V5, V6, V7); // Back Face
    glColor3f(0, 0, 1);
    Face(V0, V4, V7, V3); // Left Face
    glColor3f(1, 1, 0);
    Face(V1, V5, V6, V2); // Right Face
    glColor3f(1, 0, 1);
    Face(V2, V3, V7, V6); // Bottom Face
    glColor3f(0, 1, 1);
    Face(V0, V1, V5, V4); // Top Face
}

void Draw() {
    GLfloat V[8][3] = {
        {-0.5, 0.5, 0.5},  // V0
        {0.5, 0.5, 0.5},   // V1
        {0.5, -0.5, 0.5},  // V2
        {-0.5, -0.5, 0.5}, // V3
        {-0.5, 0.5, -0.5}, // V4
        {0.5, 0.5, -0.5},  // V5
        {0.5, -0.5, -0.5}, // V6
        {-0.5, -0.5, -0.5} // V7
    };

    GLfloat IV[8][3];
    int i, a = 2;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat r = d * 3.14 / 180;

    if (a == 1) { // Rotation about the X-axis
        for (i = 0; i < 8; i++) {
            IV[i][1] = V[i][1] * cos(r) - V[i][2] * sin(r);
            IV[i][2] = V[i][2] * cos(r) + V[i][1] * sin(r);
            IV[i][0] = V[i][0];
        }
    }

    if (a == 2) { // Rotation about the Y-axis
        for (i = 0; i < 8; i++) {
            IV[i][2] = V[i][2] * cos(r) - V[i][0] * sin(r);
            IV[i][1] = V[i][1];
            IV[i][0] = V[i][2] * sin(r) + V[i][0] * cos(r);
        }
    }

    if (a == 3) { // Rotation about the Z-axis
        for (i = 0; i < 8; i++) {
            IV[i][0] = V[i][0] * cos(r) - V[i][1] * sin(r);
            IV[i][1] = V[i][0] * sin(r) + V[i][1] * cos(r);
            IV[i][2] = V[i][2];
        }
    }

    Cube(IV[0], IV[1], IV[2], IV[3], IV[4], IV[5], IV[6], IV[7]);
    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("CUBE SPIN");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Spin);
    glutMainLoop();
    return 0;
}
