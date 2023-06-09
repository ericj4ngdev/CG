#include "Include.h"

void Player::init() {
	mPos = Vector2D(300, 0);		// �ʱ���ġ
	mVelo = Vector2D(2, 2);
	mSize = Vector2D(50, 50);
	m_Texid = NULL;
	mColor = Color4f(1, 1, 1, 1);
	gravity = 4;
	OnGround = false;
	OnCollide = false;
	JumpPower = 100;
	MoveSpeed = 2.0f;
	loadTexture();
}

void Player::Transform()
{
	Top = mPos.y - mSize.y / 2;
	Bottom = mPos.y + mSize.y / 2;
	Right = mPos.x + mSize.x / 2;
	Left = mPos.x - mSize.x / 2;

	vLT = Vector2D(Left, Top);
	vRT = Vector2D(Right, Top);
	vRB = Vector2D(Right, Bottom);
	vLB = Vector2D(Left, Bottom);
}

void Player::Render()
{
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	glBindTexture(GL_TEXTURE_2D, m_Texid);
	// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

	// ������ ������ �����ϴ� �Լ�
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ

	// ��ǥ�� �߽����� �̵�
	// ���� ��� 
	// glTranslatef((mSize.x / 2) + mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y - (mSize.y / 2), 0);
	// ���߾� ����, ������ ���� ���
	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x, mSize.y, 1);
	// if(this->Collide())

	// Collide(other)

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
}

bool Player::Collide(Sprite other)
{
	// �� �˻��ؼ� ��ġ�� 
	// bottom > other.top (�Ϲ� ��ǥ)
	// �ǽð��̶� ������ ��� X
	if ((Right >= other.Left)
		&& (Left <= other.Right)
		&& (Bottom >= other.Top)
		&& (Top <= other.Bottom))
	{
		OnCollide = true;
		return true;
	}
	OnCollide = false;
	return false; // �浹 ���� ����.
}


void Player::Move()
{
	// if (OnGround)		// ���̸�
	// 	mVelo.y = 0.0f;
	// else               // ���� �ƴϸ� 
	// {
	// 	mPos.y += gravity;
	// }

	mPos.y += gravity;


	if (KeyDown(VK_LEFT) || KeyDown('A') || KeyDown('a'))
	{
		mPos.x -= mVelo.x;
	}

	if (KeyDown(VK_RIGHT) || KeyDown('D') || KeyDown('d'))
	{
		mPos.x += mVelo.x;
	}

	// OnGround ���� &&�� �߰� 
	// if ((KeyDown(VK_UP) || KeyDown('W') || KeyDown('w')) && OnGround)
	// {
	// 	mPos.y -= JumpPower;
	// }

	if ((KeyDown(VK_UP) || KeyDown('W') || KeyDown('w')))
	{
		mPos.y -= mVelo.y;
	}

	// if (KeyDown(VK_DOWN) || KeyDown('S') || KeyDown('s'))
	// {
	// 		mPos.y += mVelo.y;
	// }
}

void Player::IsGround(Sprite& other) {
	// player �ٴ��� �ٸ� sprite�� Top�� �´����� y�� �ӵ��� 0�� �ȴ�. 
	if ((other.Top - Bottom <= 0.001f)
		&& (Right > other.Left
			&& (Left < other.Right))) OnGround = true;
	else OnGround = false;
}