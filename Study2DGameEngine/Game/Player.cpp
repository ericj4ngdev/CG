#include "Include.h"

void Player::init() {
	mPos = Vector2D(100, 0);		// 초기위치
	mVelo = Vector2D(2, 2);
	mSize = Vector2D(100, 100);
	m_Texid = NULL;
	mColor = Color4f(1, 1, 1, 1);
	gravity = 4;
	OnGround = false;
	JumpPower = 100;

	loadTexture();
}

void Player::Render()
{
	Top = mPos.y - mSize.y / 2;
	Bottom = mPos.y + mSize.y / 2;
	Right = mPos.x + mSize.x / 2;
	Left = mPos.x - mSize.x / 2;

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

bool Player::Collide(Sprite& other)
{
	// 축 검사해서 겹치면 
	// bottom > other.top (일반 좌표)
	// 실시간이라 변수로 계산 X
	if ((Right >= other.mPos.x - other.mSize.x / 2)
		&& (Left <= other.mPos.x + other.mSize.x / 2)
		&& (Bottom >= g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y + other.mSize.y / 2))
		&& (Top <= g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y - other.mSize.y / 2)))
	{
		return true;
	}
	return false; // 충돌 하지 않음.
}

void Player::Move() 
{
	if (OnGround)		// 땅이면
		mVelo.y = 0.0f;
	else               // 땅이 아니면 
	{
		mPos.y += gravity;
	}

	if (KeyDown(VK_LEFT) || KeyDown('A') || KeyDown('a'))
	{
		mPos.x -= mVelo.x;
	}

	if (KeyDown(VK_RIGHT) || KeyDown('D') || KeyDown('d'))
	{
		mPos.x += mVelo.x;
	}

	// OnGround 조건 &&로 추가 
	if ((KeyDown(VK_UP) || KeyDown('W') || KeyDown('w')) && OnGround)
	{
		mPos.y -= JumpPower;
	}

	// if (KeyDown(VK_DOWN) || KeyDown('S') || KeyDown('s'))
	// {
	// 		mPos.y += mVelo.y;
	// }
}

void Player::IsGround(Sprite& other) {
	// player 바닥이 다른 sprite의 Top과 맞닿으면 y축 속도는 0이 된다. 
	if((- Bottom + (g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y + other.mSize.y / 2)) <= 0.1)
		&& (Right > (other.mPos.x - other.mSize.x / 2))
		&& (Left < (other.mPos.x + other.mSize.x / 2))) OnGround = true;
	else OnGround = false;
}