#include <GL/glut.h>

GLuint textureID; // 텍스처 식별자

void loadTexture()
{
    // 텍스처 로드 및 생성
    glGenTextures(1, &textureID); // 텍스처 식별자 생성
    glBindTexture(GL_TEXTURE_2D, textureID); // 생성한 텍스처를 바인딩하여 설정

    // 텍스처 매개변수 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 이미지 데이터 로드
    // ...

    // 텍스처 데이터 설정
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // 사각형 이동
    glTranslatef(0.5f, 0.5f, 0.0f);

    // 텍스처 바인딩
    glBindTexture(GL_TEXTURE_2D, textureID);

    // 사각형 그리기
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);    glVertex3f(-0.5f, -0.5f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);    glVertex3f(0.5f, -0.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);    glVertex3f(0.5f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);    glVertex3f(-0.5f, 0.5f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Texture Example");

    // 텍스처 로드 및 생성
    loadTexture();

    glutDisplayFunc(renderScene);

    glutMainLoop();
    return 0;
}
