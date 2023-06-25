#include "Include.h"

void Ground::initPos()
{
	// mPos = Vector2D(300, 300);
	mSize = Vector2D(60, 50);
	m_Texid = NULL;
	mColor = Color4f(0, 0, 0, 1);
	OnCollide = false;
	loadTexture();
}

void Ground::initTexture(const char *name) {
	// mPos = Vector2D(150, 850);		// �ʱ���ġ
	mSize = Vector2D(60, 50);

	m_Tex.LoadImage(name);
	m_Texid = NULL;
	m_Texid = *m_Tex.GetTexture();

	mColor = Color4f(1, 1, 1, 1);
	OnGround = false;
	OnCollide = false;
}

void Ground::Transform()
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

void Ground::Render()
{
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	glBindTexture(GL_TEXTURE_2D, m_Texid);		// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		// ������ ������ �����ϴ� �Լ�

	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ

	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);	  // â �ϴ�
	glScalef(mSize.x, mSize.y, 1);	// â �ϴ� �� ä���

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
}

bool Ground::Collide(Sprite other)
{
	// �� �˻��ؼ� ��ġ�� 
	// bottom > other.top (�Ϲ� ��ǥ)
	// �ǽð��̶� ������ ��� X
	if ((mRight >= other.mLeft)
		&& (mLeft <= other.mRight)
		&& (mBottom >= other.mTop)
		&& (mTop <= other.mBottom))
	{
		return true;
	}
	return false; // �浹 ���� ����.
}

bool Ground::CollidebyVector(Sprite& other)
{
	OnCollide = Collide(other);

	Vector2D o1 = other.vLT;
	Vector2D o2 = other.vRT;
	Vector2D o3 = other.vRB;
	Vector2D o4 = other.vLB;

	Vector2D c1 = mPos;
	Vector2D c2 = other.mPos;

	Vector2D g1 = vLT;
	Vector2D g2 = vRT;
	Vector2D g3 = vRB;
	Vector2D g4 = vLB;

	Vector2D Ocrosspoint;
	Vector2D Gcrosspoint;
	Vector2D PushVector;

	// Ocrosspoint
	cal(o1, o2, c1, c2, Ocrosspoint);
	cal(o2, o3, c1, c2, Ocrosspoint);
	cal(o3, o4, c1, c2, Ocrosspoint);
	cal(o4, o1, c1, c2, Ocrosspoint);

	// Gcrosspoint
	cal(g1, g2, c1, c2, Gcrosspoint);
	cal(g2, g3, c1, c2, Gcrosspoint);
	cal(g3, g4, c1, c2, Gcrosspoint);
	cal(g4, g1, c1, c2, Gcrosspoint);

	PushVector = Gcrosspoint - Ocrosspoint;

	// Gcrosspoint.print(); std::cout << '\n';
	// Ocrosspoint.print(); std::cout << '\n';
	// PushVector.print(); std::cout << '\n';

	if (OnCollide)
	{
		if (PushVector.x > 1) PushVector.x = 1;
		if (PushVector.x < -1) PushVector.x = -1;
		if (PushVector.y > 1) PushVector.y = 1;
		if (PushVector.y < -1) PushVector.y = -1;

		if (fabs(PushVector.x) > fabs(PushVector.y)) {
			other.mPos.x += PushVector.x;
			other.OnGround = false;		// ���� ó��
		}
		else {
			other.mPos.y += PushVector.y - 4;		// 4�� player�� gravity�̴�. 
			other.OnGround = true;		// 
		}
		// player�� OnGround ������ �ٲ۴�. 
		// if(other.OnGround) PushVector.print();
		// printf(other.OnGround);
		other.Transform();
		return true;
	}

	other.OnGround = (false || other.OnGround);
	return false; // �浹 ���� ����.
}

// ������ ���θ� ������ crosspoint ���
void Ground::cal(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, Vector2D& cross)
{
	float num, den;
	float t;
	float ab = ccw(v1, v2, v3) * ccw(v1, v2, v4);
	float cd = ccw(v3, v4, v1) * ccw(v3, v4, v2);

	num = ((v3.x - v1.x) * (v4.y - v3.y)) - ((v4.x - v3.x) * (v3.y - v1.y));
	den = ((v2.x - v1.x) * (v4.y - v3.y)) - ((v4.x - v3.x) * (v2.y - v1.y));
	// if (den != 0) 
	t = num / den;	// ���� ����
	// else t = 1;
	if (t <= 1 && t > 0 && ab <= 0 && cd <= 0)
	{
		// std::cout << t;
		cross = v1 * (1 - t) + v2 * t;
	}
}

float Ground::ccw(Vector2D a, Vector2D b) {
	return a.cross(b);
}

float Ground::ccw(Vector2D p, Vector2D a, Vector2D b) {
	return ccw(a - p, b - p);
}
