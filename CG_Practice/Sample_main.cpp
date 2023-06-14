#include <GL/glut.h>
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
using namespace std;

// image width and height
int width, height;

//이미지 파일 열기
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

// texture 설정
void init()
{
    GLuint texID;

    unsigned char* bitmap;
    bitmap = LoadMeshFromFile((char*)"Image/block.png");
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    free(bitmap);
}

void drawBox()
{
    glBegin(GL_POLYGON);
    glTexCoord2d(0.0, 1.0);      glVertex3d(-0.5, -0.5, 0.0);
    glTexCoord2d(0.0, 0.0);      glVertex3d(-0.5, 0.5, 0.0);
    glTexCoord2d(1.0, 0.0);      glVertex3d(0.5, 0.5, 0.0);
    glTexCoord2d(1.0, 1.0);      glVertex3d(0.5, -0.5, 0.0);
    glEnd();
}

void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawBox();

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
    glutMainLoop();
    return 0;
}