#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <windows.h> // GetTickCount64 함수 사용을 위해 필요
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
using namespace std;

// image width and height
int width, height;
DWORD startTime; // 시작 시간 저장 변수
int i = 0;
int k = 0;
bool isinc = true;
bool isDown = false;
bool isStream = false;
float y = -0.5f;
bool isIdle = true;
bool isWalk = true;
bool isAttack = true;

enum State
{
    IDLE,
    WALK,
    ATTACK,
};
State currentState = IDLE;

// 키 입력함수
static int KeyDown(int vk)
{
    // GetAsyncKeyState() 함수는 해당 가상 키 코드의 상태를 반환 
    // 반환된 값에 0x8000을 AND 연산하여 키가 현재 눌려있는지 확인할 수 있다.
    // 눌리면 삼항연산자에 의해 1을 return한다. 
    return ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0);
}

static int KeyUp(int vk)
{
    return ((GetAsyncKeyState(vk) & 0x8000) ? 0 : 1);
}

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

    glTexCoord2d(8 / 433.0, 146 / 742.0);     glVertex3d(-4.0 / 15.0, -0.5, 0.0);      // 왼쪽 아래    
    glTexCoord2d(8 / 433.0, 115 / 742.0);     glVertex3d(-4.0 / 15.0, 0.5, 0.0);       // 왼쪽 위
    glTexCoord2d(25 / 433.0, 115 / 742.0);     glVertex3d(4.0 / 15.0, 0.5, 0.0);       // 오른쪽 위
    glTexCoord2d(25 / 433.0, 146 / 742.0);     glVertex3d(4.0 / 15.0, -0.5, 0.0);      // 오른쪽 아래

    glEnd();
}

void Walk(int x)        // Walk
{
    
    glBegin(GL_POLYGON);

        glTexCoord2d((8 + 40 * x ) / 433.0, 146 / 742.0);     glVertex3f(-4.0 / 15.0, -0.5, 0.0);      // 왼쪽 아래    
        glTexCoord2d((8 + 40 * x ) / 433.0, 115 / 742.0);     glVertex3d(-4.0 / 15.0, 0.5, 0.0);       // 왼쪽 위
        glTexCoord2d((25 + 40 * x ) / 433.0, 115 / 742.0);     glVertex3d(4.0 / 15.0, 0.5, 0.0);        // 오른쪽 위
        glTexCoord2d((25 + 40 * x ) / 433.0, 146 / 742.0);     glVertex3d(4.0 / 15.0, -0.5, 0.0);       // 오른쪽 아래

    glEnd();
    // y = y + 0.1f;
    // glLoadIdentity();
    // glTranslatef(y, 0.5, 0);
}

void Attack(int x)
{
    glBegin(GL_POLYGON);
    if (x == 2) // 채찍
    {
        glTexCoord2d(92 / 433.0, 186 / 742.0);     glVertex3d(-0.5, -0.33, 0.0);      // 왼쪽 아래    
        glTexCoord2d(92 / 433.0, 153 / 742.0);     glVertex3d(-0.5, 0.33, 0.0);       // 왼쪽 위
        glTexCoord2d(142 / 433.0, 153 / 742.0);     glVertex3d(0.5, 0.33, 0.0);        // 오른쪽 위
        glTexCoord2d(142 / 433.0, 186 / 742.0);     glVertex3d(0.5, -0.33, 0.0);       // 오른쪽 아래
    }
    else 
    {
        glTexCoord2d((1 + 40 * x) / 433.0, 186 / 742.0);     glVertex3d(-0.75, -0.33, 0.0);       // 왼쪽 아래    
        glTexCoord2d((1 + 40 * x) / 433.0, 153 / 742.0);     glVertex3d(-0.75, 0.33, 0.0);        // 왼쪽 위
        glTexCoord2d((33 + 40 * x) / 433.0, 153 / 742.0);     glVertex3d(-0.15, 0.33, 0.0);         // 오른쪽 위
        glTexCoord2d((33 + 40 * x) / 433.0, 186 / 742.0);     glVertex3d(-0.15, -0.33, 0.0);        // 오른쪽 아래
    }

    glEnd();
}

void InputKey()
{
    // 맨처음엔 isDown이 false이어서 입력 가능
    if (KeyDown(VK_RIGHT) && !isDown)
    {        
        startTime = GetTickCount64();     // 누른 시점
        isIdle = false;
        isWalk = true;
        isDown = true;
    }
    else {
        isIdle = true;
    }
    
    // 입력 종료
    if (!KeyDown(VK_RIGHT)) { isWalk = false; isIdle = true;  isDown = false;  i = 0; }

    DWORD currentTime = GetTickCount64();         // 시스템 시간 
    
    // 눌리면 실행
    if (isDown) 
    {
        // 애니메이션 전환부
        if ((currentTime - startTime) >= 200)     // 0.2초
        {
            if (i == 0) { isinc = true; }
            if (i == 2) { isinc = false; }
            if (isinc) i++;
            else i--;
            // 전환 후, 다시 입력 가능
            isDown = false;
        }
    }
    // 눌렸다면 0.2초간 startTime 은 고정    
    
    Walk(i);    
}
void Animation(float x) {
    DWORD currentTime = GetTickCount64();
    // 0.2초 뒤에 다음 장면 재생
    if ((currentTime - x) >= 200)  k++;
    // 계속 랜더링
    Attack(k);
    printf("print");
    
    // k = 0;
}
void InputKey_2()
{
    if ((KeyDown('Z') || KeyDown('z')) && !isDown)
    {
        startTime = GetTickCount64();      // 누른 시점
        isIdle = false;
        isAttack = true;
        isDown = true;
        
        Animation(startTime);
    }
    else isIdle = true;

    // 입력 종료코드
    if (!(KeyDown('Z') || KeyDown('z')))
    {
        isDown = false; isAttack = false;
    }
    Attack(k);
}



void controller() {    
    // printf("before : %d \n", currentState);
    // printf("%d", i);
    if (KeyDown(VK_RIGHT)) 
    {
        currentState = WALK;
    }
    if (KeyDown('Z') || KeyDown('z')) 
    {
        currentState = ATTACK;
    }

    switch (currentState) {
    case IDLE:
        Idle();
        break;
    case WALK:
        InputKey();
        if (!isWalk) {
            // i = 0;
            currentState = IDLE;
        }
        break;
    case ATTACK:
        InputKey_2();
        if (!isAttack) {
            currentState = IDLE;
        }
        break;
    default:
        std::cout << "Invalid state" << std::endl;
        break;
    }
    // printf("after : %d \n", currentState);    
}


void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    controller();
    
    // InputKey_2();
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