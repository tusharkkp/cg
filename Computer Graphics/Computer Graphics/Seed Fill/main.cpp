#include <GL/glut.h>

int W=500,H=500;

// replace color for seed fill
float fillColor[3] = {0,1,0};   // green
float seedColor[3] = {0,0,0};   // background (initial)

// put pixel
void putPixel(int x,int y,float col[3]){
    glColor3f(col[0],col[1],col[2]);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

// compare colors
bool sameColor(float a[3], float b[3]){
    return (a[0]==b[0] && a[1]==b[1] && a[2]==b[2]);
}

void seedFill(int x,int y){
    float pix[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pix);
    if(sameColor(pix,seedColor)){
        putPixel(x,y,fillColor);
        glFlush();
        seedFill(x+1,y);
        seedFill(x-1,y);
        seedFill(x,y+1);
        seedFill(x,y-1);
    }
}

void drawPolygon(){
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150,150);
    glVertex2i(350,150);
    glVertex2i(350,350);
    glVertex2i(150,350);
    glEnd();
    glFlush();
}

void mouse(int btn,int state,int x,int y){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        seedFill(x, H-y);
    }
}

void init(){
    glClearColor(0,0,0,1);
    gluOrtho2D(0,W,0,H);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(W,H);
    glutCreateWindow("Seed Fill");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
