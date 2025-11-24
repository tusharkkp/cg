#include <GL/glut.h>

int W=500,H=500;
float fillColor[3] = {1,1,0};     // yellow fill
float boundaryColor[3] = {1,1,1}; // white boundary

void putPixel(int x,int y,float col[3]){
    glColor3f(col[0],col[1],col[2]);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

bool same(float a[3], float b[3]){
    return (a[0]==b[0] && a[1]==b[1] && a[2]==b[2]);
}

void boundaryFill(int x,int y){
    float pix[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pix);
    if(!same(pix,boundaryColor) && !same(pix,fillColor)){
        putPixel(x,y,fillColor);
        glFlush();
        boundaryFill(x+1,y);
        boundaryFill(x-1,y);
        boundaryFill(x,y+1);
        boundaryFill(x,y-1);
    }
}

void drawTriangle(){
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150,100);
    glVertex2i(300,300);
    glVertex2i(450,100);
    glEnd();
    glFlush();
}

void mouse(int btn,int state,int x,int y){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        boundaryFill(x, H-y);
    }
}

void init(){
    glClearColor(0,0,0,1);
    gluOrtho2D(0,W,0,H);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawTriangle();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(W,H);
    glutCreateWindow("Boundary Fill");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
