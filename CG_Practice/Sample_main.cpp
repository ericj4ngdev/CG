#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <windows.h> // GetTickCount64 �Լ� ����� ���� �ʿ�

DWORD startTime; // ���� �ð� ���� ����
bool drawRectangle = false; // �簢�� �׸��� ���� ����

// Ű �Է��Լ�
static int KeyDown(int vk)
{
    return ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0);
}

static int KeyUp(int vk)
{
    return ((GetAsyncKeyState(vk) & 0x8000) ? 0 : 1);
}


void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void drawRect(float size)
{
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(size, 0);
    glVertex2f(size, size);
    glVertex2f(0, size);
    glEnd();
}

void specialFunc()
{
    if (KeyDown('Z') || KeyDown('z'))
    {
        startTime = GetTickCount64(); // ���� �ð� ����
        drawRectangle = true;
    }
}

void render()
{
    specialFunc();

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (drawRectangle) {
        DWORD currentTime = GetTickCount64(); // ���� �ð� ����

        // ��� �ð��� 3�ʰ� �Ǹ� �簢�� �׸��� �ߴ�
        if ((currentTime - startTime) >= 250)
            drawRectangle = false;

        drawRect(100);
    }

    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3-Second Rectangle");

    init();

    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutMainLoop();

    return 0;
}