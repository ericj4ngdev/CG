#include "Include.h"
void Enemy::initPos() {
	// mPos = Vector2D(550, 850 / 2);		// �ʱ���ġ
	mVelo = Vector2D(2, 2);
	mSize = Vector2D(50, 50);
	
	m_Texid = NULL;
	
	mColor = Color4f(0.1, 0.1, 0.8, 0.5);
	MoveSpeed = 2.0f;
	gravity = 4;
	OnGround = false;
	OnCollide = false;
	loadTexture();
}

void Enemy::initTexture(const char *name)
{
	// mPos = Vector2D(550, 850 / 2);		// �ʱ���ġ
	mVelo = Vector2D(2, 2);
	mSize = Vector2D(50, 100);

	m_Tex.LoadImage(name);
	m_Texid = NULL;
	m_Texid = *m_Tex.GetTexture();

	mColor = Color4f(1, 1, 1, 1);
	MoveSpeed = 2.0f;
	gravity = 4;
	OnGround = false;
	OnCollide = false;
}
void Enemy::Transform()
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

void Enemy::Render()
{
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	glBindTexture(GL_TEXTURE_2D, m_Texid);
	// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

	// ������ ������ �����ϴ� �Լ�
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ

	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x, mSize.y, 1);

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
}


bool Enemy::Collide(Sprite other)
{
	// �� �˻��ؼ� ��ġ�� 
	// bottom > other.top (�Ϲ� ��ǥ)
	// �ǽð��̶� ������ ��� X
	if ((mRight >= other.mLeft)
		&& (mLeft <= other.mRight)
		&& (mBottom >= other.mTop)
		&& (mTop <= other.mBottom))
	{
		OnCollide = true;
		return true;
	}
	OnCollide = false;
	return false; // �浹 ���� ����.
}

void Enemy::InputController() 
{
	mPos.y += gravity;
	mPos.x -= mVelo.x;
}
