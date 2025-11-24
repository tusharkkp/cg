#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <algorithm>

const float LANE_X[3] = {-2.0f, 0.0f, 2.0f};
const float SEGMENT_LENGTH = 4.0f;
const float GAME_SPEED = 0.25f;        // world forward speed (lower = slower)
const int   SPAWN_INTERVAL_FRAMES = 45; // lower = more frequent obstacles
const int   MAX_OBSTACLES = 12;
const int   WINDOW_W = 1000;
const int   WINDOW_H = 700;
const bool  DEBUG_PRINTS = false;      // set true for extra console logs
// ----------------------------------------

struct Obstacle { int lane; float z; bool active; float size; };

std::vector<Obstacle> obstacles;
float worldOffset = 0.0f;   // increases to move world toward player
int frameCounter = 0;
int scoreVal = 0;
bool gameOver = false;

// player state
int playerLane = 1;
float playerX = LANE_X[1];
float playerY = 0.0f;
bool isJumping = false;
float jumpVel = 0.0f;

// spawning helper
void spawnObstacle() {
    if ((int)obstacles.size() >= MAX_OBSTACLES) return;
    Obstacle o;
    o.lane = rand() % 3;
    // put obstacle ahead, relative z before worldOffset is added in draw
    o.z = - (SEGMENT_LENGTH * 35.0f) - (rand() % 200); // far ahead
    o.active = true;
    o.size = 0.8f + (rand()%100)/200.0f;
    obstacles.push_back(o);
    if (DEBUG_PRINTS) std::cout<<"Spawned obs lane="<<o.lane<<" z="<<o.z<<"\n";
}

void drawBitmapString(float x, float y, void *font, const char* s) {
    glRasterPos2f(x, y);
    for (const char* c = s; *c; c++) glutBitmapCharacter(font, *c);
}

void drawGroundSegment(float z0, float z1) {
    // simple textured-like center path + grass either side
    glBegin(GL_QUADS);
      glColor3f(0.35f, 0.28f, 0.18f);
      glVertex3f(-3.5f, 0.0f, z0);
      glVertex3f( 3.5f, 0.0f, z0);
      glVertex3f( 3.5f, 0.0f, z1);
      glVertex3f(-3.5f, 0.0f, z1);
    glEnd();
    glBegin(GL_QUADS);
      glColor3f(0.05f, 0.45f, 0.1f);
      glVertex3f(-8.0f, 0.0f, z0);
      glVertex3f(-3.5f, 0.0f, z0);
      glVertex3f(-3.5f, 0.0f, z1);
      glVertex3f(-8.0f, 0.0f, z1);
    glEnd();
    glBegin(GL_QUADS);
      glColor3f(0.05f, 0.45f, 0.1f);
      glVertex3f(8.0f, 0.0f, z0);
      glVertex3f(3.5f, 0.0f, z0);
      glVertex3f(3.5f, 0.0f, z1);
      glVertex3f(8.0f, 0.0f, z1);
    glEnd();
}

void drawTreeAt(float x, float z) {
    glPushMatrix();
      glTranslatef(x, 0.0f, z);
      // trunk
      glColor3f(0.45f,0.28f,0.15f);
      glPushMatrix();
        glTranslatef(0.0f,0.9f,0.0f);
        glScalef(0.4f,1.8f,0.4f);
        glutSolidCube(1.0f);
      glPopMatrix();
      // leaves
      glColor3f(0.06f,0.5f,0.12f);
      glPushMatrix();
        glTranslatef(0.0f,2.0f,0.0f);
        glutSolidCone(1.2f,1.6f,12,6);
      glPopMatrix();
    glPopMatrix();
}

void drawObstacle(const Obstacle &o, float drawZ) {
    glPushMatrix();
      glTranslatef(LANE_X[o.lane], 0.5f, drawZ);
      glScalef(o.size, o.size, o.size);
      glColor3f(0.8f,0.1f,0.1f);
      glutSolidCube(1.0f);
    glPopMatrix();
}

void drawPlayer() {
    glPushMatrix();
      glTranslatef(playerX, playerY + 0.9f, 0.0f);
      // body
      glColor3f(0.15f,0.5f,0.9f);
      glPushMatrix();
        glTranslatef(0.0f,0.1f,0.0f);
        glScalef(0.6f,0.9f,0.4f);
        glutSolidCube(1.0f);
      glPopMatrix();
      // head
      glColor3f(1.0f,0.9f,0.8f);
      glPushMatrix();
        glTranslatef(0.0f,0.95f,0.0f);
        glutSolidSphere(0.22f,12,12);
      glPopMatrix();
      // legs simple
      glColor3f(0.1f,0.1f,0.1f);
      glPushMatrix();
        glTranslatef(-0.18f,-0.35f,0.0f);
        glScalef(0.18f,0.55f,0.18f);
        glutSolidCube(1.0f);
      glPopMatrix();
      glPushMatrix();
        glTranslatef(0.18f,-0.35f,0.0f);
        glScalef(0.18f,0.55f,0.18f);
        glutSolidCube(1.0f);
      glPopMatrix();
    glPopMatrix();
}

void drawHUD() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
        glLoadIdentity();
        glColor3f(1.0f,1.0f,1.0f);
        std::ostringstream ss; ss << "Score: " << scoreVal;
        drawBitmapString(10, WINDOW_H - 20, GLUT_BITMAP_HELVETICA_18, ss.str().c_str());
        if (gameOver) {
            const char* s = "GAME OVER - Press R to restart";
            drawBitmapString(WINDOW_W/2 - 160, WINDOW_H/2, GLUT_BITMAP_HELVETICA_18, s);
        }
      glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // fixed camera behind player looking forward
    float camX = playerX;
    float camY = 3.2f;
    float camZ = 6.0f;
    gluLookAt(camX, camY, camZ,
              playerX, 1.0f, -10.0f,
              0.0f, 1.0f, 0.0f);

    // lighting
    GLfloat lightpos[] = { -10.0f, 10.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    // draw many ground segments to create path illusion
    for (int i = 0; i < 60; ++i) {
        float z0 = - (i * SEGMENT_LENGTH) + fmod(worldOffset, SEGMENT_LENGTH);
        float z1 = z0 - SEGMENT_LENGTH;
        drawGroundSegment(z0, z1);
    }

    // draw trees on sides (world coordinates shift with worldOffset)
    for (int i = -35; i < 10; ++i) {
        float z = i * 6.5f + fmod(worldOffset*0.6f, 6.5f);
        drawTreeAt(-6.0f, z);
        drawTreeAt(6.0f, z - 2.4f);
    }

    // draw obstacles (convert their stored z by adding worldOffset so they approach player)
    for (auto &o : obstacles) {
        if (!o.active) continue;
        float drawZ = o.z + worldOffset;
        // Only draw visible range
        if (drawZ < 10.0f && drawZ > -80.0f) drawObstacle(o, drawZ);
    }

    // player is always at z=0 in world coordinates
    drawPlayer();

    // HUD
    drawHUD();

    glutSwapBuffers();
}

bool collisionWith(const Obstacle &o) {
    float px = playerX;
    float pz = 0.0f;
    float ox = LANE_X[o.lane];
    float oz = o.z + worldOffset;
    float dx = fabs(px - ox);
    float dz = fabs(pz - oz);
    // player small height check via playerY
    if (dx < 0.9f && dz < 1.1f && playerY < 0.9f) return true;
    return false;
}

void idleOrTimer(int value) {
    if (!gameOver) {
        frameCounter++;
        worldOffset += GAME_SPEED; // move world toward player
        // spawn occasionally
        if (frameCounter % SPAWN_INTERVAL_FRAMES == 0) spawnObstacle();

        // update obstacles: if they pass player, deactivate & update score
        for (auto &o : obstacles) {
            if (!o.active) continue;
            if (o.z + worldOffset > 6.0f) { // passed player
                o.active = false;
                scoreVal += 5;
                if (DEBUG_PRINTS) std::cout<<"Obstacle passed. score="<<scoreVal<<"\n";
            }
        }
        // remove inactive obstacles occasionally
        if (frameCounter % 30 == 0) {
            obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                            [](const Obstacle &x){ return !x.active; }), obstacles.end());
        }

        // jump physics
        if (isJumping) {
            playerY += jumpVel;
            jumpVel -= 0.022f;
            if (playerY <= 0.0f) { playerY = 0.0f; isJumping = false; jumpVel = 0.0f; }
        }

        // smooth lane movement
        float targetX = LANE_X[playerLane];
        playerX += (targetX - playerX) * 0.22f;

        // collision detection
        for (auto &o : obstacles) {
            if (!o.active) continue;
            if (collisionWith(o)) {
                gameOver = true;
                std::cout<<"Game Over! Score: "<<scoreVal<<"\n";
                break;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, idleOrTimer, 0); // ~60 FPS timer
}

void keyboard(unsigned char key, int x, int y) {
    if (gameOver && (key=='r' || key=='R')) {
        // restart
        obstacles.clear();
        worldOffset = 0.0f;
        frameCounter = 0;
        scoreVal = 0;
        gameOver = false;
        playerLane = 1; playerX = LANE_X[playerLane]; playerY = 0.0f;
        return;
    }
    switch (key) {
        case 27: exit(0); break;
        case 'a': case 'A': if (playerLane>0) playerLane--; break;
        case 'd': case 'D': if (playerLane<2) playerLane++; break;
        case ' ': if (!isJumping) { isJumping=true; jumpVel=0.36f; } break;
        default: break;
    }
}

void specialKeys(int k, int, int) {
    if (k == GLUT_KEY_LEFT) if (playerLane>0) playerLane--;
    if (k == GLUT_KEY_RIGHT) if (playerLane<2) playerLane++;
}

void reshape(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w/(double)h, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    srand((unsigned int)time(nullptr));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutCreateWindow("Temple Run Clone");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat amb[] = {0.18f,0.18f,0.18f,1.0f};
    GLfloat diff[] = {0.9f,0.9f,0.9f,1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb); glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

    glClearColor(0.55f,0.8f,0.95f,1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, idleOrTimer, 0);

    std::cout<<"Controls: A/D or Left/Right to change lane, Space to jump, R to restart.\n";
    glutMainLoop();
    return 0;
}
