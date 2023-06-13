#include "Include.h"
DWORD startTime = 0; // ���� �ð��� �����ϴ� ����

void Player::init() {
	this->mTransform.mPos = Vector2D(500, 0);		// �ʱ���ġ
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
		DWORD currentTime = GetTickCount64(); // ���� �ð� ����

		// ��� �ð��� 0.25�ʰ� �Ǹ� �簢�� �׸��� �ߴ�
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
	// 	JumpPower -= 0.5f;		// �� �����Ӹ��� ���������� ���ش�. 
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
//	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
//	glBindTexture(GL_TEXTURE_2D, m_Texid);
//	// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�
//
//	// ������ ������ �����ϴ� �Լ�
//	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);
//
//	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
//	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ
//
//	glTranslatef(mPos.x + 150, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
//	glScalef(-mSize.x * 4, mSize.y / 4, 1);
//
//	DrawBox(1);
//
//	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
//	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
//}

//void Player::IsGround(Sprite& other) 
//{
//	// player �ٴ��� �ٸ� sprite�� Top�� �´����� y�� �ӵ��� 0�� �ȴ�. 
//	if (other.Top - Bottom <= 0.1f) OnGround = true;
//	else OnGround = false;
//} 