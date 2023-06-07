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

bool Player::Collide(Sprite& other)
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

bool Player::CollidebyVector(Sprite& other)
{
	float t = 0;
	float p = 0;
	float num1, den1;
	float num2, den2;

	Vector2D g1 = other.vLT;
	Vector2D g2 = other.vRT;
	Vector2D g3 = other.vRB;
	Vector2D g4 = other.vLB;

	Vector2D c1 = mPos;
	Vector2D c2 = other.mPos;
	
	Vector2D p1 = vLT;
	Vector2D p2 = vRT;
	Vector2D p3 = vRB;
	Vector2D p4 = vLB;

	Vector2D Gcrosspoint;
	Vector2D Pcrosspoint;

	// Gcrosspoint
	num1 = ((c1.x - g1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (c1.y - g1.y));
	den1 = ((g2.x - g1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (g2.y - g1.y));
	t = num1 / den1;
	Gcrosspoint = g1 * (1 - t) + g2 * t;
	
	// Pcrosspoint
	num2 = ((c1.x - p4.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (c1.y - p4.y));
	den2 = ((p3.x - p4.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (p3.y - p4.y));
	p = num2 / den2;
	Pcrosspoint = p4 * (1 - p) + p3 * p;

	// Gcrosspoint.print(); std::cout << '\n';
	// Pcrosspoint.print(); std::cout << '\n';
	// (Gcrosspoint - Pcrosspoint).print(); std::cout << '\n';
	
	if (OnGround)
	{
		mPos.y += (Gcrosspoint - Pcrosspoint).y - gravity;
		// gravity = 0;
		// ���� : (crosspoint - p4); ���� ����
		// ũ�� : (crosspoint - bottom)
		return true;
	}
	return false; // �浹 ���� ����.
}
/// <summary>
/// 
/// </summary>
/// <param name="v1"></param> ground
/// <param name="v2"></param> ground
/// <param name="v3"></param> player
/// <param name="v4"></param> player
//void Player::cal(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4) 
//{
//	float num1, den1;
//	float num2, den2;
//	Vector2D c1 = mPos;
//	Vector2D c2 = other.mPos;
//
//	num1 = ((c1.x - v1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (c1.y - v1.y));
//	den1 = ((v2.x - v1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (v2.y - v1.y));
//	t = num1 / den1;
//	Gcrosspoint = g1 * (1 - t) + g2 * t;
//
//	// Pcrosspoint
//	num2 = ((c1.x - p4.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (c1.y - p4.y));
//	den2 = ((p3.x - p4.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (p3.y - p4.y));
//	p = num2 / den2;
//	Pcrosspoint = p4 * (1 - p) + p3 * p;
//}


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
	if((other.Top - Bottom <= 0.001f)
		&& (Right > other.Left
		&& (Left < other.Right))) OnGround = true;
	else OnGround = false;
}