#include "Include.h"

void Player::init() {
	mPos = Vector2D(300, 0);		// �ʱ���ġ
	mVelo = Vector2D(2, 2);
	mSize = Vector2D(100, 100);
	m_Texid = NULL;
	mColor = Color4f(1, 1, 1, 1);
	gravity = 4;
	OnGround = false;
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
	if ((Right >= other.mPos.x - other.mSize.x / 2)
		&& (Left <= other.mPos.x + other.mSize.x / 2)
		&& (Bottom >= g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y + other.mSize.y / 2))
		&& (Top <= g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y - other.mSize.y / 2)))
	{
		return true;
	}
	return false; // �浹 ���� ����.
}

bool Player::CollidebyVector(Sprite& other)
{
	// �� �� 
	float t, s = 0;
	float num1, den1;
	float num2, den2;
	Vector2D g1 = other.vLT;
	Vector2D g2 = other.vRT;
	Vector2D c1 = mPos;
	Vector2D c2 = other.mPos;
	Vector2D p1 = vLB;
	Vector2D p2 = vRB;
	Vector2D Gcrosspoint;
	Vector2D Pcrosspoint;
	num1 = ((c1.x - g1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (c1.y - g1.y));
	den1 = ((g2.x - g1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (g2.y - g1.y));

	num2 = ((c1.x - p1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (c1.y - p1.y));
	den2 = ((p2.x - p1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (p2.y - p1.y));

	std::cout << num1 << "  " << den1 << '\n';
	t = num1 / den1;
	s = num2 / den2;
	//p1.print(); std::cout << '\n';
	//p2.print(); std::cout << '\n';
	std::cout << t << '\n';

	// printf(t);
	// std::cout << t;

	Gcrosspoint = g1 * (1 - t) + g2 * t;
	Pcrosspoint = p1 * (1 - s) + p2 * s;

	// ���� = ohter�� ���п� ����
	// ũ�� = ħ���� �� ~ �浹����
	// �ٵ� ħ���ߴ��� ���ߴ��� ��ĳ �Ƴ�...
	
	if (OnGround)
	{
		// mPos.y -= Bottom - crosspoint.y;
		mPos = Gcrosspoint - c2 ;// -Pcrosspoint);
		gravity = 0;
		// ���� : (crosspoint - p4); ���� ����
		// ũ�� : (crosspoint - bottom)
		return true;
	}
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

	if (KeyDown(VK_DOWN) || KeyDown('S') || KeyDown('s'))
	{
		mPos.y += mVelo.y;
	}
}

void Player::IsGround(Sprite& other) {
	// player �ٴ��� �ٸ� sprite�� Top�� �´����� y�� �ӵ��� 0�� �ȴ�. 
	if((- Bottom + (g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y + other.mSize.y / 2)) <= 0.1)
		&& (Right > (other.mPos.x - other.mSize.x / 2))
		&& (Left < (other.mPos.x + other.mSize.x / 2))) OnGround = true;
	else OnGround = false;
}