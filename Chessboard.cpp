#include <GL/glut.h>
#include <cmath>

int gridSize = 8;
float angleX = 0.0f;
float angleY = 0.0f;
int prevMouseX = 0;
int prevMouseY = 0;
bool isRotating = false;

void drawChessboard() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if ((i + j) % 2 == 0) {
                glColor3f(1.0, 1.0, 1.0);
            }
            else {
                glColor3f(0.0, 0.0, 0.0);
            }

            glPushMatrix();
            glTranslatef(i - gridSize / 2, 0.0, j - gridSize / 2);
            glScalef(1.0, 0.2, 1.0);
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
}

void drawWoodenBoard() {
    glColor3f(0.6, 0.4, 0.2);

    glPushMatrix();
    glTranslatef(-0.5, -0.3, -0.5);
    glScalef(8.5, 0.5, 8.5);
    glutSolidCube(1.0); 
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 15.0, 
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);
    glRotatef(angleY, 1.0, 0.0, 0.0);
    glRotatef(angleX, 0.0, 1.0, 0.0);
    drawWoodenBoard();
    drawChessboard();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            prevMouseX = x;
            prevMouseY = y;
            isRotating = true;
        }
        else if (state == GLUT_UP) {
            isRotating = false;
        }
    }
}

void motion(int x, int y) {
    if (isRotating) {
        int dx = x - prevMouseX;
        int dy = y - prevMouseY;
        angleX += dx;
        angleY += dy;
        prevMouseX = x;
        prevMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating 3D Chessboard with Wooden Board");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}
