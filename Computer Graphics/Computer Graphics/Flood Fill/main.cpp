#include <GL/glut.h>

int W=500,H=500;
float oldColor[3] = {0,0,0};  // initial area
float newColor[3] = {1,0,0};  // red fill

void putPixel(int x,int y,float col[3]){
    glColor3f(col[0],col[1],col[2]);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

bool same(float a[3], float b[3]){
    return (a[0]==b[0] && a[1]==b[1] && a[2]==b[2]);
}

void floodFill(int x,int y){
    float pix[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pix);
    if(same(pix,oldColor)){
        putPixel(x,y,newColor);
        glFlush();
        floodFill(x+1,y);
        floodFill(x-1,y);
        floodFill(x,y+1);
        floodFill(x,y-1);
    }
}

void polygon(){
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(200,200);
    glVertex2i(300,250);
    glVertex2i(350,150);
    glVertex2i(250,100);
    glVertex2i(150,150);
    glEnd();
    glFlush();
}

void mouse(int btn,int state,int x,int y){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        floodFill(x, H-y);
    }
}

void init(){
    glClearColor(0,0,0,1);
    gluOrtho2D(0,W,0,H);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    polygon();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(W,H);
    glutCreateWindow("Flood Fill");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
