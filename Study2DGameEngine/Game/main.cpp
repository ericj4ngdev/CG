#include "Include.h"
WindowSize g_Extern;

Stage* mStage = NULL;
#pragma region mStage
// mStage 초기화
void init() {
    if (mStage == NULL) {
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

// mStage 자원 해제
void Release() {
    if (mStage != NULL) {
        mStage->Release();
        delete mStage;
        mStage == NULL;
    }
}

// mStage 이동
void FrameMove() {
    if (mStage != NULL) {
        mStage->FrameMove();
    }
}
#pragma endregion




void renderScene()
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("3D Tech- GLUT Tutorial");
    glutDisplayFunc(renderScene);
    glutMainLoop();

    return 0;
}