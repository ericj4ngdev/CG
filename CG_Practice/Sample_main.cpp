#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <windows.h> // GetTickCount64 �Լ� ����� ���� �ʿ�
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
using namespace std;

// image width and height
int width, height;
DWORD startTime; // ���� �ð� ���� ����
int i = 0;
int k = 0;
bool isinc = true;
bool isDown = false;
bool isStream = false;

// Ű �Է��Լ�
static int KeyDown(int vk)
{
    // GetAsyncKeyState() �Լ��� �ش� ���� Ű �ڵ��� ���¸� ��ȯ 
    // ��ȯ�� ���� 0x8000�� AND �����Ͽ� Ű�� ���� �����ִ��� Ȯ���� �� �ִ�.
    // ������ ���׿����ڿ� ���� 1�� return�Ѵ�. 
    return ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0);
}

static int KeyUp(int vk)
{
    return ((GetAsyncKeyState(vk) & 0x8000) ? 0 : 1);
}

//�̹��� ���� ����
unsigned char* LoadMeshFromFile(const char* texFile)
{
    GLuint texture;
    glGenTextures(1, &texture);
    FILE* fp = NULL;
    if (fopen_s(&fp, texFile, "rb")) {
        printf("ERROR : No %s. \n fail to bind %d\n", texFile, texture);
        return (unsigned char*)false;
    }
    int channel;
    unsigned char* image = stbi_load_from_file(fp, &width, &height, &channel, 4);
    fclose(fp);
    return image;
}

// texture ����
void init()
{
    GLuint texID;

    unsigned char* bitmap;
    bitmap = LoadMeshFromFile((char*)"Image/castlevania3.png");

    glEnable(GL_TEXTURE_2D);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    free(bitmap);
}

void Idle() 
{
    glBegin(GL_POLYGON);

    glTexCoord2d(8 / 433.0, 146 / 742.0);     glVertex3d(-4.0 / 15.0, -0.5, 0.0);      // ���� �Ʒ�    
    glTexCoord2d(8 / 433.0, 115 / 742.0);     glVertex3d(-4.0 / 15.0, 0.5, 0.0);       // ���� ��
    glTexCoord2d(25 / 433.0, 115 / 742.0);     glVertex3d(4.0 / 15.0, 0.5, 0.0);        // ������ ��
    glTexCoord2d(25 / 433.0, 146 / 742.0);     glVertex3d(4.0 / 15.0, -0.5, 0.0);       // ������ �Ʒ�

    glEnd();
}

void Walk(int x)        // Walk
{
    glBegin(GL_POLYGON);

        glTexCoord2d((8 + 40 * x ) / 433.0, 146 / 742.0);     glVertex3d(-4.0 / 15.0, -0.5, 0.0);      // ���� �Ʒ�    
        glTexCoord2d((8 + 40 * x ) / 433.0, 115 / 742.0);     glVertex3d(-4.0 / 15.0, 0.5, 0.0);       // ���� ��
        glTexCoord2d((25 + 40 * x ) / 433.0, 115 / 742.0);     glVertex3d(4.0 / 15.0, 0.5, 0.0);        // ������ ��
        glTexCoord2d((25 + 40 * x ) / 433.0, 146 / 742.0);     glVertex3d(4.0 / 15.0, -0.5, 0.0);       // ������ �Ʒ�
    
    glEnd();
}

void Attack(int x)
{
    glBegin(GL_POLYGON);
    if (x == 2) // ä��
    {
        glTexCoord2d(92 / 433.0, 186 / 742.0);     glVertex3d(-0.5, -0.33, 0.0);      // ���� �Ʒ�    
        glTexCoord2d(92 / 433.0, 153 / 742.0);     glVertex3d(-0.5, 0.33, 0.0);       // ���� ��
        glTexCoord2d(142 / 433.0, 153 / 742.0);     glVertex3d(0.5, 0.33, 0.0);        // ������ ��
        glTexCoord2d(142 / 433.0, 186 / 742.0);     glVertex3d(0.5, -0.33, 0.0);       // ������ �Ʒ�
    }
    else 
    {
        glTexCoord2d((1 + 40 * x) / 433.0, 186 / 742.0);     glVertex3d(-0.75, -0.33, 0.0);       // ���� �Ʒ�    
        glTexCoord2d((1 + 40 * x) / 433.0, 153 / 742.0);     glVertex3d(-0.75, 0.33, 0.0);        // ���� ��
        glTexCoord2d((33 + 40 * x) / 433.0, 153 / 742.0);     glVertex3d(-0.15, 0.33, 0.0);         // ������ ��
        glTexCoord2d((33 + 40 * x) / 433.0, 186 / 742.0);     glVertex3d(-0.15, -0.33, 0.0);        // ������ �Ʒ�
    }

    glEnd();
}

void InputKey()
{
    // printf("%d", i);
    if (KeyDown(VK_RIGHT) && !isDown)
    {
        startTime = GetTickCount64();      // ���� ����
        isDown = true;
    }
    DWORD currentTime = GetTickCount64();         // �ý��� �ð� 
    if (isDown)
    {
        if ((currentTime - startTime) >= 200)     // 0.2��
        {
            if (i == 0) { isinc = true; }
            if (i == 2) { isinc = false; }
            if (isinc) i++;
            else i--;
            isDown = false;                       // �ٽ� ������ �ְ� ��
        }
    }
    Walk(i);
}

void InputKey_2()
{
    if ((KeyDown('Z') || KeyDown('z')) && !isDown)
    {
        startTime = GetTickCount64();      // ���� ����
        isDown = true;
    }

    DWORD currentTime = GetTickCount64();         // �ý��� �ð� 
    if (isDown)
    {
        if ((currentTime - startTime) >= 200)     // 0.2��
        {
            if (k == 2) { k = 0; }
            else k++;
            isDown = false;                       // �ٽ� ������ �ְ� ��
        }
    }
    Attack(k);
}


void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // InputKey();
    InputKey_2();
    // Attack(k);
    // Walk();
    glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 30.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("image");
    glutReshapeFunc(reshape);
    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}