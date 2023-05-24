#include <gl/glut.h>
// #include<gl/gl.h>

float angle = 0.0;
float red = 1.0, blue = 1.0, green = 1.0;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);

    // 여기서 실제 색을 설정합니다.
    // glColor 는 앞으로 그려질 물체들의 색을 결정합니다.
    glColor3f(red, green, blue);

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    // 모델링 변환을 마치고나서
    // 카메라설정을 원래대로 돌려놓습니다.
    glPopMatrix();

    // 마지막으로 angle 변수에 1 을 더해줍니다.
    angle += 0.1f;

    // 위에서 그린것을 보여주기 위해서 버퍼를 교체합니다.
    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    //창이 아주 작을 때, 0 으로 나누는 것을 예방합니다.
    if (h == 0) h = 1;
    float ratio = 1.0 * w / h;

    //좌표계를 수정하기 전에 초기화합니다.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //뷰포트를 창의 전체 크기로 설정합니다.
    glViewport(0, 0, w, h);

    //투시값을 설정합니다.
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 
        0.0, 0.0, -1.0, 0.0f,
        1.0f, 0.0f);
}

void processSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F1:
        red = 1.0;
        green = 0.0;
        blue = 0.0; break;
    case GLUT_KEY_F2:
        red = 0.0;
        green = 1.0;
        blue = 0.0; break;
    case GLUT_KEY_F3:
        red = 0.0;
        green = 0.0;
        blue = 1.0; break;
    }
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);

    //이중버퍼를 설정한다.
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("3D Tech- GLUT Tutorial");
    glutDisplayFunc(renderScene);

    //휴면(idle)시간에 호출될 함수를 설정한다.
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    // glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    //깊이 검사가 가능하도록 설정한다.
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}