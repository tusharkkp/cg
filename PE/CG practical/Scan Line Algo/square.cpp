#include <GL/glut.h>
#include <vector>
#include <algorithm>

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

void scanLineFill(int y, const std::vector<std::pair<int, int>>& edges, float fillColor[3]) {
    std::vector<int> intersections;

    for (size_t i = 0; i < edges.size(); i++) {
        int x1 = edges[i].first, y1 = edges[i].second;
        int x2 = edges[(i + 1) % edges.size()].first, y2 = edges[(i + 1) % edges.size()].second;

        if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
            int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
            intersections.push_back(x);
        }
    }

    std::sort(intersections.begin(), intersections.end());

    for (size_t i = 0; i < intersections.size(); i += 2) {
        for (int x = intersections[i]; i + 1 < intersections.size() && x <= intersections[i + 1]; x++) {
            setPixel(x, y, fillColor[0], fillColor[1], fillColor[2]);
        }
    }
}

void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 150);
    glVertex2i(350, 150);
    glVertex2i(350, 350);
    glVertex2i(150, 350);
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();

    float fillColor[] = {0.0, 0.0, 1.0};
    std::vector<std::pair<int, int>> edges = {{150, 150}, {350, 150}, {350, 350}, {150, 350}};

    for (int y = 150; y <= 350; y++) {
        scanLineFill(y, edges, fillColor);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Scan Line Filling - Square");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
