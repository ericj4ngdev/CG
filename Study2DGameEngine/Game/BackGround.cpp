#include "Include.h"

void BackGround::initTexture(const char* name) {
	float s;
	s = 3;
	mPos = Vector2D(2960,500);		// 초기위치
	mSize = Vector2D(3600 * s, 410 * s);

	m_Tex.LoadImage(name);
	m_Texid = NULL;
	m_Texid = *m_Tex.GetTexture();

	mColor = Color4f(1, 1, 1, 1);
	OnGround = false;
}

void BackGround::Transform()
{
	mTop = mPos.y - mSize.y / 2;
	mBottom = mPos.y + mSize.y / 2;
	mRight = mPos.x + mSize.x / 2;
	mLeft = mPos.x - mSize.x / 2;

	vLT = Vector2D(mLeft, mTop);
	vRT = Vector2D(mRight, mTop);
	vRB = Vector2D(mRight, mBottom);
	vLB = Vector2D(mLeft, mBottom);
}

void BackGround::Render()
{
	glPushMatrix();			// 현재 모델뷰 행렬을 스택에 저장하는 함수
	glBindTexture(GL_TEXTURE_2D, m_Texid);		// 현재 활성화된 텍스처 유닛에 2D 텍스처를 바인딩하는 함수

	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		// 현재의 색상을 설정하는 함수

	glMatrixMode(GL_MODELVIEW);			// 현재의 행렬 모드를 설정하는 함수
	glLoadIdentity();					// 현재 행렬을 단위 행렬로 초기화

	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);	  // 창 하단
	glScalef(-mSize.x, mSize.y, 1);	// 창 하단 다 채우기

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수
}