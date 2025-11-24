#include <GL/glut.h>

float s = 1.0;
float zoom = 0.02;

void drawScaledTriangle(float s){
    glBegin(GL_TRIANGLES);
        glVertex2f(150*s + 200, 100*s + 200);
        glVertex2f(250*s + 200, 100*s + 200);
        glVertex2f(200*s + 200, 200*s + 200);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    drawScaledTriangle(s);
    glutSwapBuffers();
}

void update(int value){
    s += zoom;
    if(s > 2.0 || s < 0.5) zoom *= -1;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init(){
    glClearColor(0,0,0,1);
    gluOrtho2D(0,600,0,600);
}

int main(int argc,char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Animated Scaling");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
}
