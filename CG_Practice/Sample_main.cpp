#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// �̹��� ���� �̸���
std::vector<std::string> imageFiles = { "1.png", "2.png", "3.png" };

// ���� ǥ�� ���� �̹��� �ε���
int currentImageIndex = 0;

// �̹��� ���� ���� (0.2��)
const int imageChangeInterval = 200;

// �̹��� ���� �ð� üũ�� ����
std::chrono::steady_clock::time_point lastImageChangeTime = std::chrono::steady_clock::now();

void drawImage()
{
    // �̹��� �׸��� ����
    // �� �κ��� ������ �̹����� �׸��� �ڵ�� ��ü�ؾ� �մϴ�.
    // ���÷� ���� ǥ�� ���� �̹����� �ε����� ����մϴ�.
    std::cout << "Current Image Index: " << currentImageIndex << std::endl;
}

void changeImage()
{
    // �̹��� ���� ����
    currentImageIndex = (currentImageIndex + 1) % imageFiles.size();
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawImage();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        // Spacebar�� ������ �� �̹��� ����
        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> elapsedTime = currentTime - lastImageChangeTime;

        if (elapsedTime.count() >= imageChangeInterval)
        {
            changeImage();
            lastImageChangeTime = currentTime;
        }
    }
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Image Animation");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
