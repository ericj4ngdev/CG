#include "Include.h"

bool Collider::Collide(Sprite other)
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

bool Collider::CollidebyVector(Player& other)
{
	Vector2D o1 = other.mSprite.vLT;
	Vector2D o2 = other.mSprite.vRT;
	Vector2D o3 = other.mSprite.vRB;
	Vector2D o4 = other.mSprite.vLB;

	Vector2D c1 = mTransform.mPos;
	Vector2D c2 = other.mTransform.mPos;

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
		if (fabs(PushVector.x) > fabs(PushVector.y))
			other.mPos.x += PushVector.x;
		else
			other.mPos.y += PushVector.y - 4;		// 4�� player�� gravity�̴�. 
		other.OnGround = true;						// player�� OnGround ������ �ٲ۴�. 
		other.Transform();
		return true;
	}
	// other.OnGround = false;
	return false; // �浹 ���� ����.
}

// ������ ���θ� ������ crosspoint ���
void Collider::cal(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, Vector2D& cross)
{
	float num, den;
	float t;
	float ab = ccw(v1, v2, v3) * ccw(v1, v2, v4);
	float cd = ccw(v3, v4, v1) * ccw(v3, v4, v2);

	num = ((v3.x - v1.x) * (v4.y - v3.y)) - ((v4.x - v3.x) * (v3.y - v1.y));
	den = ((v2.x - v1.x) * (v4.y - v3.y)) - ((v4.x - v3.x) * (v2.y - v1.y));
	t = num / den;
	if (t <= 1 && t > 0 && ab <= 0 && cd <= 0)
	{
		// std::cout << t;
		cross = v1 * (1 - t) + v2 * t;
	}
}

float Collider::ccw(Vector2D a, Vector2D b) {
	return a.cross(b);
}

float Collider::ccw(Vector2D p, Vector2D a, Vector2D b) {
	return ccw(a - p, b - p);
}