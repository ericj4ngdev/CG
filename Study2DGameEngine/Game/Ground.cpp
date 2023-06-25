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
	// mPos = Vector2D(150, 850);		// 초기위치
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
	glPushMatrix();			// 현재 모델뷰 행렬을 스택에 저장하는 함수
	glBindTexture(GL_TEXTURE_2D, m_Texid);		// 현재 활성화된 텍스처 유닛에 2D 텍스처를 바인딩하는 함수

	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		// 현재의 색상을 설정하는 함수

	glMatrixMode(GL_MODELVIEW);			// 현재의 행렬 모드를 설정하는 함수
	glLoadIdentity();					// 현재 행렬을 단위 행렬로 초기화

	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);	  // 창 하단
	glScalef(mSize.x, mSize.y, 1);	// 창 하단 다 채우기

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수
}

bool Ground::Collide(Sprite other)
{
	// 축 검사해서 겹치면 
	// bottom > other.top (일반 좌표)
	// 실시간이라 변수로 계산 X
	if ((mRight >= other.mLeft)
		&& (mLeft <= other.mRight)
		&& (mBottom >= other.mTop)
		&& (mTop <= other.mBottom))
	{
		return true;
	}
	return false; // 충돌 하지 않음.
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
			other.OnGround = false;		// 옆면 처리
		}
		else {
			other.mPos.y += PushVector.y - 4;		// 4는 player의 gravity이다. 
			other.OnGround = true;		// 
		}
		// player의 OnGround 변수를 바꾼다. 
		// if(other.OnGround) PushVector.print();
		// printf(other.OnGround);
		other.Transform();
		return true;
	}

	other.OnGround = (false || other.OnGround);
	return false; // 충돌 하지 않음.
}

// 내분점 여부를 따지고 crosspoint 계산
void Ground::cal(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, Vector2D& cross)
{
	float num, den;
	float t;
	float ab = ccw(v1, v2, v3) * ccw(v1, v2, v4);
	float cd = ccw(v3, v4, v1) * ccw(v3, v4, v2);

	num = ((v3.x - v1.x) * (v4.y - v3.y)) - ((v4.x - v3.x) * (v3.y - v1.y));
	den = ((v2.x - v1.x) * (v4.y - v3.y)) - ((v4.x - v3.x) * (v2.y - v1.y));
	// if (den != 0) 
	t = num / den;	// 무한 방지
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
