#include <GL/glut.h>
#include <cmath>

int gridSize = 8; // Size of the chessboard grid
float angleX = 0.0f; // Rotation angle around X-axis
float angleY = 0.0f; // Rotation angle around Y-axis
int prevMouseX = 0; // Previous mouse X position
int prevMouseY = 0; // Previous mouse Y position
bool isRotating = false; // Flag to track mouse rotation

void drawChessboard() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if ((i + j) % 2 == 0) {
                glColor3f(1.0, 1.0, 1.0); // White square
            }
            else {
                glColor3f(0.0, 0.0, 0.0); // Black square
            }

            glPushMatrix();
            glTranslatef(i - gridSize / 2, 0.0, j - gridSize / 2); // Position the square
            glScalef(1.0, 0.2, 1.0);
            glutSolidCube(1.0); // Draw a unit cube as a square
            glPopMatrix();
        }
    }
}

void drawWoodenBoard() {
    glColor3f(0.6, 0.4, 0.2); // Brown color for the wooden board

    glPushMatrix();
    glTranslatef(-0.5, -0.3, -0.5); // Position the wooden board below the chessboard
    glScalef(8.5, 0.5, 8.5); // Scale the wooden board
    glutSolidCube(1.0); // Draw a large wooden cube
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the camera position
    gluLookAt(5.0, 5.0, 15.0,  // Eye position
        0.0, 0.0, 0.0,        // Look-at point
        0.0, 1.0, 0.0);       // Up vector

    // Apply mouse-based rotation
    glRotatef(angleY, 1.0, 0.0, 0.0);
    glRotatef(angleX, 0.0, 1.0, 0.0);

    // Draw the wooden board
    drawWoodenBoard();

    // Draw the chessboard
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