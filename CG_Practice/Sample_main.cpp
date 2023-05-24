#include <gl/glut.h>
// #include<gl/gl.h>

float angle = 0.0;
float red = 1.0, blue = 1.0, green = 1.0;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);

    // ���⼭ ���� ���� �����մϴ�.
    // glColor �� ������ �׷��� ��ü���� ���� �����մϴ�.
    glColor3f(red, green, blue);

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    // �𵨸� ��ȯ�� ��ġ����
    // ī�޶����� ������� ���������ϴ�.
    glPopMatrix();

    // ���������� angle ������ 1 �� �����ݴϴ�.
    angle += 0.1f;

    // ������ �׸����� �����ֱ� ���ؼ� ���۸� ��ü�մϴ�.
    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    //â�� ���� ���� ��, 0 ���� ������ ���� �����մϴ�.
    if (h == 0) h = 1;
    float ratio = 1.0 * w / h;

    //��ǥ�踦 �����ϱ� ���� �ʱ�ȭ�մϴ�.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //����Ʈ�� â�� ��ü ũ��� �����մϴ�.
    glViewport(0, 0, w, h);

    //���ð��� �����մϴ�.
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

    //���߹��۸� �����Ѵ�.
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("3D Tech- GLUT Tutorial");
    glutDisplayFunc(renderScene);

    //�޸�(idle)�ð��� ȣ��� �Լ��� �����Ѵ�.
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    // glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    //���� �˻簡 �����ϵ��� �����Ѵ�.
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}