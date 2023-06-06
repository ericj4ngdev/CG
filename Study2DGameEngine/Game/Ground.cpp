#include "Include.h"

void Ground::init()
{
	mPos = Vector2D(300, 300);
	mSize = Vector2D(100, 100);
	m_Texid = NULL;
	mColor = Color4f(0, 0, 0, 1);
	OnCollide = false;
	loadTexture();
}

void Ground::Transform()
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

bool Ground::CollidebyVector(Sprite& other)
{
	float g = 0;
	float p = 0;
	float num1, den1;
	float num2, den2;
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

	// Ocrosspoint
	cal(o1, o2, c1, c2, Ocrosspoint);
	cal(o2, o3, c1, c2, Ocrosspoint);
	cal(o3, o4, c1, c2, Ocrosspoint);
	cal(o4, o1, c1, c2, Ocrosspoint);
	// num1 = ((c1.x - o1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (c1.y - o1.y));
	// den1 = ((o2.x - o1.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (o2.y - o1.y));
	// g = num1 / den1;
	// if (g <= 1 && g >= 0) 
	// {
	// 	Gcrosspoint = o1 * (1 - g) + o2 * g;
	// }

	// Gcrosspoint
	cal(g1, g2, c1, c2, Gcrosspoint);
	cal(g2, g3, c1, c2, Gcrosspoint);
	cal(g3, g4, c1, c2, Gcrosspoint);
	cal(g4, g1, c1, c2, Gcrosspoint);
	// num2 = ((c1.x - g4.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (c1.y - g4.y));
	// den2 = ((g3.x - g4.x) * (c2.y - c1.y)) - ((c2.x - c1.x) * (g3.y - g4.y));
	// p = num2 / den2;
	// Gcrosspoint = g4 * (1 - p) + g3 * p;

	Gcrosspoint.print(); std::cout << '\n';
	Ocrosspoint.print(); std::cout << '\n';
	(Gcrosspoint - Ocrosspoint).print(); std::cout << '\n';

	if (OnCollide)
	{
		other.mPos += Ocrosspoint - Gcrosspoint;
		// other.mPos += (Gcrosspoint - Pcrosspoint);
		// 
		// gravity = 0;
		// ���� : (crosspoint - p4); ���� ����
		// ũ�� : (crosspoint - bottom)
		return true;
	}
	return false; // �浹 ���� ����.
}

bool Ground::Collide(Sprite& other)
{
	// �� �˻��ؼ� ��ġ�� 
	// bottom > other.top (�Ϲ� ��ǥ)
	// �ǽð��̶� ������ ��� X
	if ((Right >= other.Left)
		&& (Left <= other.Right)
		&& (Bottom >= other.Top)
		&& (Top <= other.Bottom))
	{
		return true;
	}
	return false; // �浹 ���� ����.
}

// ������ ���θ� ������ crosspoint ���
void Ground::cal(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, Vector2D& cross)
{
	float num, den;
	float t;
	double ab = ccw(v1, v2, v3) * ccw(v1, v2, v4);
	double cd = ccw(v3, v4, v1) * ccw(v3, v4, v2);

	num = ((v3.x - v1.x) * (v4.y - v3.y)) - ((v4.x - v3.x) * (v3.y - v1.y));
	den = ((v2.x - v1.x) * (v4.y - v3.y)) - ((v4.x - v3.x) * (v2.y - v1.y));
	t = num / den;
	if (t <= 1 && t > 0 && ab <= 0 && cd <= 0)
	{
		std::cout << t;
		cross = v1 * (1 - t) + v2 * t;
	}
}

double Ground::ccw(Vector2D a, Vector2D b) {
	return a.cross(b);
}

double Ground::ccw(Vector2D p, Vector2D a, Vector2D b) {
	return ccw(a - p, b - p);
}


void Ground::Render(int num) 
{
	
}
