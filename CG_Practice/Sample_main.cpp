#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// 이미지 파일 이름들
std::vector<std::string> imageFiles = { "1.png", "2.png", "3.png" };

// 현재 표시 중인 이미지 인덱스
int currentImageIndex = 0;

// 이미지 변경 간격 (0.2초)
const int imageChangeInterval = 200;

// 이미지 변경 시간 체크용 변수
std::chrono::steady_clock::time_point lastImageChangeTime = std::chrono::steady_clock::now();

void drawImage()
{
    // 이미지 그리는 로직
    // 이 부분을 실제로 이미지를 그리는 코드로 대체해야 합니다.
    // 예시로 현재 표시 중인 이미지의 인덱스를 출력합니다.
    std::cout << "Current Image Index: " << currentImageIndex << std::endl;
}

void changeImage()
{
    // 이미지 변경 로직
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
        // Spacebar를 눌렀을 때 이미지 변경
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
