#include<glut.h>
#include <iostream>
#include "Include.h"

using namespace std;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, -0.5, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{

    Vector2D v1(1, 2), v2(3,4);
    Vector2D v3 = v1 + v2;
    v1.getx();

    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("3D Tech- GLUT Tutorial");
    glutDisplayFunc(renderScene);
    glutMainLoop();

    return 0;
}