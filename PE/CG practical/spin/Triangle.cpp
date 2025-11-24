#include <GL/glut.h>
#include <math.h>

GLfloat d = 0; 

void MyInit() {
    glClearColor(0, 0, 0, 1); 
    glEnable(GL_DEPTH_TEST);  
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat color[]) {
    glBegin(GL_TRIANGLES);
    glColor3fv(color); 
    glVertex3fv(A);    
    glVertex3fv(B);    
    glVertex3fv(C);    
    glEnd();
}


void Draw() {

    GLfloat V[4][3] = {
        {0.0, 0.5, 0.0},
        {-0.5, -0.5, 0.5}, 
        {0.5, -0.5, 0.5},  
        {0.0, -0.5, -0.5}  
    };

    GLfloat colors[4][3] = {
        {1, 0, 0}, 
        {0, 1, 0}, 
        {0, 0, 1}, 
        {1, 1, 0}  
    };

    GLfloat rV[4][3]; 
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity(); 

    GLfloat r = d * M_PI / 180; 

    
    for (i = 0; i < 4; i++) {
        rV[i][0] = V[i][0]; 
        rV[i][1] = V[i][1] * cos(r) - V[i][2] * sin(r); 
        rV[i][2] = V[i][1] * sin(r) + V[i][2] * cos(r); 
    }

    
    Face(rV[0], rV[1], rV[2], colors[0]); 
    Face(rV[0], rV[1], rV[3], colors[1]); 
    Face(rV[0], rV[2], rV[3], colors[2]); 
    Face(rV[1], rV[2], rV[3], colors[3]); 

    glutSwapBuffers(); 
}


void Spin() {
    d += 0.10; 
    if (d > 360) d -= 360; 
    glutPostRedisplay(); 
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);                    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
    glutCreateWindow("Spinning Triangle");           

    MyInit();                                        
    glutDisplayFunc(Draw);                           
    glutIdleFunc(Spin);                              
    glutMainLoop();                                  

    return 0;
}
