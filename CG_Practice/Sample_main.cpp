#include <gl/glut.h>
#include <gl/gl.h>

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
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
}

// 텍스처 이미지 데이터
GLubyte textureImage[64][64][3];

void init()
{
    // 텍스처 이미지 데이터 초기화
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            // 텍스처 이미지 생성 (여기서는 단순히 색상 설정)
            textureImage[i][j][0] = 255;  // 빨간색
            textureImage[i][j][1] = 0;    // 초록색
            textureImage[i][j][2] = 0;    // 파란색
        }
    }

    // 텍스처 매핑 설정
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // 텍스처 좌표 자동 생성 설정
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // 텍스처 좌표 자동 생성 활성화
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // 광원 및 뷰 설정
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

    // 삼각형 그리기
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