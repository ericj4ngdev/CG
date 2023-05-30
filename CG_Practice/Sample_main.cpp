#include <gl/glut.h>
#include <gl/gl.h>

void changeSize(int w, int h)
{
    //â�� ���� ���� ��, 0 ���� ������ ���� �����մϴ�.
    if (h == 0)
        h = 1;
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
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
}

// �ؽ�ó �̹��� ������
GLubyte textureImage[64][64][3];

void init()
{
    // �ؽ�ó �̹��� ������ �ʱ�ȭ
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            // �ؽ�ó �̹��� ���� (���⼭�� �ܼ��� ���� ����)
            textureImage[i][j][0] = 255;  // ������
            textureImage[i][j][1] = 0;    // �ʷϻ�
            textureImage[i][j][2] = 0;    // �Ķ���
        }
    }

    // �ؽ�ó ���� ����
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // �ؽ�ó ��ǥ �ڵ� ���� ����
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // �ؽ�ó ��ǥ �ڵ� ���� Ȱ��ȭ
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // ���� �� �� ����
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // �ﰢ�� �׸���
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 0.0); glVertex3f(0.0, 0.5, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, -0.5, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, -0.5, -1.0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Texture Triangle");

    init();

    glutDisplayFunc(display);
    // glutReshapeFunc(changeSize);

    glutMainLoop();

    return 0;
}