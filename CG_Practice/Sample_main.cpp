#include <GL/glut.h>

GLuint textureID; // �ؽ�ó �ĺ���

void loadTexture()
{
    // �ؽ�ó �ε� �� ����
    glGenTextures(1, &textureID); // �ؽ�ó �ĺ��� ����
    glBindTexture(GL_TEXTURE_2D, textureID); // ������ �ؽ�ó�� ���ε��Ͽ� ����

    // �ؽ�ó �Ű����� ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // �̹��� ������ �ε�
    // ...

    // �ؽ�ó ������ ����
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // �簢�� �̵�
    glTranslatef(0.5f, 0.5f, 0.0f);

    // �ؽ�ó ���ε�
    glBindTexture(GL_TEXTURE_2D, textureID);

    // �簢�� �׸���
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

    // �ؽ�ó �ε� �� ����
    loadTexture();

    glutDisplayFunc(renderScene);

    glutMainLoop();
    return 0;
}
