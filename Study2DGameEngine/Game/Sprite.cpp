#include "Include.h"

void Sprite::init() 
{
	mPos = Vector2D(0, 0);		// 초기위치
	mSize = Vector2D(100, 100);
	m_Texid = NULL;
	mColor = Color4f(1, 1, 1, 1);

	loadTexture();
}

void Sprite::init(int yt)
{
	mPos = Vector2D(400, 50);
	mSize = Vector2D(600, 50);
	m_Texid = NULL;
	mColor = Color4f(0, 0, 0, 1);

	loadTexture();
}

void Sprite::loadTexture()
{
	// 텍스처 로드 및 생성
	glGenTextures(1, &m_Texid); // 텍스처 식별자 생성
	glBindTexture(GL_TEXTURE_2D, m_Texid); // 생성한 텍스처를 바인딩하여 설정

	// 텍스처 매개변수 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Sprite::Release()
{
	if (m_Texid != NULL)
	{
		glDeleteTextures(1, &m_Texid); // 텍스처 식별자 삭제
		m_Texid = 0; // 텍스처 식별자 초기화
	}
}

bool Sprite::Collide(Sprite& other)
{
	// 축 검사해서 겹치면 
	if ((mPos.x + mSize.x / 2 >= other.mPos.x - other.mSize.x / 2)
		&& (mPos.x - mSize.x / 2 <= other.mPos.x + other.mSize.x / 2))
	{
		return true;
	}
	return false; // 충돌 하지 않음.
}

void Sprite::DrawBox(float size)
{
	// 6개 면의 법선벡터
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	// 6개 면의 인덱스, 각 면은 4개의 정점으로 구성
	// 정점이 숫자로 표현. 0~7은 v로 좌표가 나옴
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	// 상자의 8개의 정점 좌표를 저장하는 2차원 배열
	GLfloat v[8][3];

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (int i = 0; i < 6; i++)
	{
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);					// 현재 면의 법선 벡터를 설정

		glTexCoord2f(0, 1);						// 텍스처 좌표 설정
		glVertex3fv(&v[faces[i][0]][0]);		// 정점 좌표를 설정. 면그리기
		glTexCoord2f(0, 0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1, 0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1, 1);
		glVertex3fv(&v[faces[i][3]][0]);

		glEnd();
	}
}

// player 전용 render함수 
void Sprite::Render() 
{
	glPushMatrix();			// 현재 모델뷰 행렬을 스택에 저장하는 함수
		glBindTexture(GL_TEXTURE_2D, m_Texid);		// 현재 활성화된 텍스처 유닛에 2D 텍스처를 바인딩하는 함수

			glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		// 현재의 색상을 설정하는 함수

			glMatrixMode(GL_MODELVIEW);			// 현재의 행렬 모드를 설정하는 함수
			glLoadIdentity();					// 현재 행렬을 단위 행렬로 초기화

			// 좌표의 중심으로 이동
			// 좌측 상단 
			// glTranslatef((mSize.x / 2) + mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y - (mSize.y / 2), 0);
			// 정중앙 기준, 시작은 좌측 상단
			glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
			glScalef(-mSize.x, mSize.y, 1);
			// if(this->Collide())

			// Collide(other)

			DrawBox(1);

		glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수
}

// ground 전용 render함수 
void Sprite::Render(int x)
{
	glPushMatrix();			// 현재 모델뷰 행렬을 스택에 저장하는 함수
	glBindTexture(GL_TEXTURE_2D, m_Texid);		// 현재 활성화된 텍스처 유닛에 2D 텍스처를 바인딩하는 함수

	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		// 현재의 색상을 설정하는 함수

	glMatrixMode(GL_MODELVIEW);			// 현재의 행렬 모드를 설정하는 함수
	glLoadIdentity();					// 현재 행렬을 단위 행렬로 초기화

	glTranslatef(mPos.x, mPos.y, 0);	  // 창 하단
	glScalef(mSize.x, mSize.y, 1);	// 창 하단 다 채우기

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수
}

