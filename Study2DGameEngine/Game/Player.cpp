#include "Include.h"

void Player::init() {
	mPos = Vector2D(0, 0);		// 초기위치
	mSize = Vector2D(100, 100);
	m_Texid = NULL;
	mColor = Color4f(1, 1, 1, 1);

	loadTexture();
}

void Player::Render()
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

void Player::Move() 
{
	if (KeyDown(VK_LEFT) || KeyDown('A') || KeyDown('a'))
	{
		mPos.x -= MoveSpeed;
	}

	if (KeyDown(VK_RIGHT) || KeyDown('D') || KeyDown('d'))
	{
		mPos.x += MoveSpeed;
	}

	if (KeyDown(VK_UP) || KeyDown('W') || KeyDown('w'))
	{
		mPos.y -= MoveSpeed;
	}

	if (KeyDown(VK_DOWN) || KeyDown('S') || KeyDown('s'))
	{
		mPos.y += MoveSpeed;
	}
}