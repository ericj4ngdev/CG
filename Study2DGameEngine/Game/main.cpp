#include "Include.h"
WindowSize g_Extern;

Stage* mStage = NULL;
float cameraX = 0.0f;
float cameraY = 0.0f;

#pragma region mStage
// mStage 초기화
void init() {
    if (mStage == NULL)
    {
        mStage = new Stage();
        mStage->init();
    }
}

// mStage 그리기
void Render() {
    if (mStage != NULL) {
        mStage->Render();
    }
}
// 위치 정보 갱신
void Transform() {
    if (mStage != NULL) {
        mStage->Transform();
    }
}

// mStage 자원 해제
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

// mStage 이동
void FrameMove() {
    if (mStage != NULL) {
        mStage->FrameMove();
    }
}
#pragma endregion

void changeSize(int w, int h)
{
    //창이 아주 작을 때, 0 으로 나누는 것을 예방합니다.
    if (h == 0)
        h = 1;
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
              0.0, 0.0, -1.0, 
              0.0f, 1.0f, 0.0f);
}

// 각 sprite 의 render와 move 담당
// 매 프레임마다 호출되는 함수로 update같다고 보면 된다. 
void display() {
    Transform();
    Collide();
    FrameMove();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glTranslatef(-cameraX, -cameraY, 0.0f);

    glViewport(0, 0, g_Extern.WINDOWSIZE_WIDTH, g_Extern.WINDOWSIZE_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-g_Extern.WINDOWSIZE_WIDTH/2, g_Extern.WINDOWSIZE_WIDTH/2, 0, g_Extern.WINDOWSIZE_HEIGHT, 0.01, 1000);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 프레임마다 이전에 그려진 색상 버퍼와 깊이 버퍼를 초기화
    glClearColor(0.5, 0.5, 0.5, 1.0); // 화면을 지우고 초기화할 때 사용할 색상을 설정합니다. 이 코드에서는 회색 배경색을 지정
    Render();
    glutSwapBuffers();      // 백버퍼와 프론트버퍼를 교환하여 화면에 그려진 결과를 표시
}

void onIdle()
{
    g_Extern.WINDOWSIZE_WIDTH = glutGet(GLUT_WINDOW_WIDTH);
    g_Extern.WINDOWSIZE_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);

    display();
    Sleep(1000.0f / 60.0f);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        cameraY += 10.0f;
        break;
    case 's':
        cameraY -= 10.0f;
        break;
    case 'a':
        cameraX -= 10.0f;
        break;
    case 'd':
        cameraX += 10.0f;
        break;
    }

    glutPostRedisplay();
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
    // glutReshapeFunc(changeSize);
    // glutKeyboardFunc(keyboard);
    // 
    // int atexit(void (*func)(void));
    // 프로그램 종료하면 자원 해재 함수 Release함수 호출
    // func는 함수 포인터. 반환값은 등록시 0, 실패시 -1 반환
    atexit(Release);
    // glutMouseFunc(onMouse);
    glutIdleFunc(onIdle);       // 실행중에도 계속 
    glutMainLoop();


    return 0;
}