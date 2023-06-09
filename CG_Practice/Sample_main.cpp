#include <GL/glut.h>

// 카메라 변수
float cameraX = 0.0f;
float cameraY = 0.0f;

// 화면 크기
int screenWidth = 800;
int screenHeight = 600;

// 사각형 위치
float rectangleX = 100.0f;
float rectangleY = 100.0f;

void drawRectangle(float x, float y, float width, float height) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(width, height, 1.0f);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 카메라 위치로 이동
    glTranslatef(-cameraX, -cameraY, 0.0f);

    // 카메라 범위 안에서만 사각형 그리기
    if (rectangleX > cameraX - screenWidth / 2 && rectangleX < cameraX + screenWidth / 2 &&
        rectangleY > cameraY - screenHeight / 2 && rectangleY < cameraY + screenHeight / 2) {
        drawRectangle(rectangleX, rectangleY, 100.0f, 100.0f);
    }

    glFlush();
}

void reshape(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        cameraY += 10.0f;
        break;
    case 's':
        cameraY -= 10.0f;
        break;
    case 'a':
        cameraX -= 10.0f;
        break;
    case 'd':
        cameraX += 10.0f;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("2D Camera Example");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glutMainLoop();
    return 0;
}
