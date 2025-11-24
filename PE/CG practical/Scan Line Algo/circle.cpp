#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <cmath>

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 500, 0, 500);
}

void setPixel(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Function to fill between intersections for each scan line
void scanLineFill(int y, int xc, int yc, int r, float fillColor[3]) {
    std::vector<int> intersections;

    // Calculate the x-coordinates of the intersections for the current y scan line
    int y_diff = y - yc;
    if (y_diff * y_diff <= r * r) {
        int x_offset = (int)sqrt(r * r - y_diff * y_diff);  // Pythagoras' theorem
        intersections.push_back(xc - x_offset);  // Left intersection
        intersections.push_back(xc + x_offset);  // Right intersection
    }

    // Fill between pairs of intersections
    for (size_t i = 0; i < intersections.size(); i += 2) {
        for (int x = intersections[i]; x <= intersections[i + 1]; x++) {
            setPixel(x, y, fillColor[0], fillColor[1], fillColor[2]);
        }
    }
}

// Function to draw the circle outline
void drawCircle(int xc, int yc, int r) {
    glColor3f(1.0, 0.0, 0.0);  // Red color for the circle outline
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180.0f;  // Convert degree to radian
        int x = xc + r * cos(theta);
        int y = yc + r * sin(theta);
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 250, yc = 250, r = 100;  // Circle center (250, 250) and radius 100
    drawCircle(xc, yc, r);

    float fillColor[] = {0.0, 0.0, 1.0};  // Blue color for filling

    // Scan line fill for the circle
    for (int y = yc - r; y <= yc + r; y++) {
        scanLineFill(y, xc, yc, r, fillColor);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Scan Line Filling - Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
