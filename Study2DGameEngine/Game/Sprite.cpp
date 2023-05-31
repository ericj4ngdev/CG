#include "Include.h"

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
