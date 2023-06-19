#include "Include.h"
WindowSize g_Extern;

Stage* mStage = NULL;

#pragma region mStage
// mStage �ʱ�ȭ
void init() {
    if (mStage == NULL)
    {
        mStage = new Stage();
        mStage->init();
    }
}

// mStage �׸���
void Render() {
    if (mStage != NULL) {
        mStage->Render();
    }
}
// ��ġ ���� ����
void Transform() {
    if (mStage != NULL) {
        mStage->Transform();
    }
}

// mStage �ڿ� ����
void Release() {
    if (mStage != NULL) {
        mStage->Release();
        delete mStage;
        mStage = NULL;
    }
}

void Collide() {
    if (mStage != NULL) {
        mStage->Collide();
    }
}

// mStage �̵�
void FrameMove() {
    if (mStage != NULL) {
        mStage->FrameMove();
    }
}
#pragma endregion

// �� sprite �� render�� move ���
// �� �����Ӹ��� ȣ��Ǵ� �Լ��� update���ٰ� ���� �ȴ�. 
void display() 
{
    Transform();
    Collide();
    FrameMove();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, g_Extern.WINDOWSIZE_WIDTH, g_Extern.WINDOWSIZE_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, g_Extern.WINDOWSIZE_WIDTH, 0, g_Extern.WINDOWSIZE_HEIGHT, 0.01, 1000);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����Ӹ��� ������ �׷��� ���� ���ۿ� ���� ���۸� �ʱ�ȭ
    glClearColor(0.5, 0.5, 0.5, 1.0); // ȭ���� ����� �ʱ�ȭ�� �� ����� ������ �����մϴ�. �� �ڵ忡���� ȸ�� ������ ����
    Render();
    glutSwapBuffers();      // ����ۿ� ����Ʈ���۸� ��ȯ�Ͽ� ȭ�鿡 �׷��� ����� ǥ��

}

void onIdle()
{
    g_Extern.WINDOWSIZE_WIDTH = glutGet(GLUT_WINDOW_WIDTH);
    g_Extern.WINDOWSIZE_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);

    display();
    Sleep(1000.0f / 60.0f);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    g_Extern.WINDOWSIZE_WIDTH = 800;
    g_Extern.WINDOWSIZE_HEIGHT = 500;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(g_Extern.WINDOWSIZE_WIDTH, g_Extern.WINDOWSIZE_HEIGHT);
    glutCreateWindow("GAME");

    glEnable(GL_TEXTURE_2D);
    init();
    glutDisplayFunc(display);
    // 
    // int atexit(void (*func)(void));
    // ���α׷� �����ϸ� �ڿ� ���� �Լ� Release�Լ� ȣ��
    // func�� �Լ� ������. ��ȯ���� ��Ͻ� 0, ���н� -1 ��ȯ
    atexit(Release);
    // glutMouseFunc(onMouse);
    glutIdleFunc(onIdle);       // �����߿��� ��� 
    glutMainLoop();


    return 0;
}