#include <GL/glut.h>

float tx = 0;     // translation amount
float speed = 2;  // translation speed

void drawTriangle() {
    glBegin(GL_TRIANGLES);
        glVertex2f(100+tx,100);
        glVertex2f(200+tx,100);
        glVertex2f(150+tx,200);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    drawTriangle();
    glutSwapBuffers();
}

void update(int value){
    tx += speed;

    if(tx > 400 || tx < 0)   // bounce back
        speed = -speed;

    glutPostRedisplay();       // redraw
    glutTimerFunc(16, update, 0);  // call again after 16ms (~60fps)
}

void init(){
    glClearColor(0,0,0,1);
    gluOrtho2D(0,600,0,600);
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Animated Translation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
}
