#include "Include.h"
DWORD startTime = 0; // 시작 시간을 저장하는 변수

void Player::init() {
	this->mTransform.mPos = Vector2D(500, 0);		// 초기위치
	this->mTransform.mSize = Vector2D(50, 100);
	this->mSprite.m_Texid = NULL;
	this->mSprite.mColor = Color4f(0, 0, 1, 1);
	
	gravity = 4;
	mVelo = Vector2D(2, 2);
	OnGround = false;
	OnCollide = false;
	JumpPower = 0;
	MoveSpeed = 2.0f;
	isAttack = false;
	mSprite.loadTexture();
}

void Player::Transform()
{
	this->mSprite.SquareArea(mTransform.mPos, mTransform.mSize);
}

void Player::Render()
{	
	this->mSprite.RenderSquare(mTransform.mPos, mTransform.mSize);

	if (isAttack) {
		DWORD currentTime = GetTickCount64(); // 현재 시간 측정

		// 경과 시간이 0.25초가 되면 사각형 그리기 중단
		if ((currentTime - startTime) >= 250)
			isAttack = false;

		// Attack();
	}
}

bool Player::Collide(cObject other)
{
	this->mCollider.CollideArea(mTransform.mPos, mTransform.mSize);
	return mCollider.Collide(other);
}

void Player::Release()
{
	this->mSprite.Release();
}


void Player::Move()
{
	this->mTransform.mPos.y += gravity - JumpPower;
	// std::cout << OnGround << '\n';
	// if (JumpPower > 0)
	// 	JumpPower -= 0.5f;		// 매 프레임마다 순차적으로 뺴준다. 
	// else
	// 	JumpPower = 0;

	if (KeyDown(VK_LEFT))
	{
		this->mTransform.mPos.x -= mVelo.x;
	}

	if (KeyDown(VK_RIGHT))
	{
		this->mTransform.mPos.x += mVelo.x;
	}

	if (KeyDown(VK_SPACE) && OnGround)
		JumpPower = 10;
	

	if (KeyDown('Z') || KeyDown('z'))
	{
		isAttack = true;
	}
	OnGround = false;
}

//void Player::Attack() 
//{
//	glPushMatrix();			// 현재 모델뷰 행렬을 스택에 저장하는 함수
//	glBindTexture(GL_TEXTURE_2D, m_Texid);
//	// 현재 활성화된 텍스처 유닛에 2D 텍스처를 바인딩하는 함수
//
//	// 현재의 색상을 설정하는 함수
//	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);
//
//	glMatrixMode(GL_MODELVIEW);			// 현재의 행렬 모드를 설정하는 함수
//	glLoadIdentity();					// 현재 행렬을 단위 행렬로 초기화
//
//	glTranslatef(mPos.x + 150, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
//	glScalef(-mSize.x * 4, mSize.y / 4, 1);
//
//	DrawBox(1);
//
//	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
//	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수
//}

//void Player::IsGround(Sprite& other) 
//{
//	// player 바닥이 다른 sprite의 Top과 맞닿으면 y축 속도는 0이 된다. 
//	if (other.Top - Bottom <= 0.1f) OnGround = true;
//	else OnGround = false;
//} 