#include "Include.h"

void Player::init() {
	mPos = Vector2D(300, 0);		// 초기위치
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
	glPushMatrix();			// 현재 모델뷰 행렬을 스택에 저장하는 함수
	glBindTexture(GL_TEXTURE_2D, m_Texid);		
	// 현재 활성화된 텍스처 유닛에 2D 텍스처를 바인딩하는 함수

	// 현재의 색상을 설정하는 함수
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		

	glMatrixMode(GL_MODELVIEW);			// 현재의 행렬 모드를 설정하는 함수
	glLoadIdentity();					// 현재 행렬을 단위 행렬로 초기화

	// 좌표의 중심으로 이동
	// 좌측 상단 
	// glTranslatef((mSize.x / 2) + mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y - (mSize.y / 2), 0);
	// 정중앙 기준, 시작은 좌측 상단
	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x, mSize.y, 1);
	// if(this->Collide())

	// Collide(other)

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수
}

bool Player::Collide(Sprite& other)
{
	// 축 검사해서 겹치면 
	// bottom > other.top (일반 좌표)
	// 실시간이라 변수로 계산 X
	if ((Right >= other.mPos.x - other.mSize.x / 2)
		&& (Left <= other.mPos.x + other.mSize.x / 2)
		&& (Bottom >= g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y + other.mSize.y / 2))
		&& (Top <= g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y - other.mSize.y / 2)))
	{
		return true;
	}
	return false; // 충돌 하지 않음.
}

bool Player::CollidebyVector(Sprite& other)
{
	// 두 선 
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

	// 방향 = ohter의 선분에 수직
	// 크기 = 침범한 점 ~ 충돌지점
	// 근데 침범했는지 안했는지 어캐 아나...
	
	if (OnGround)
	{
		// mPos.y -= Bottom - crosspoint.y;
		mPos = Gcrosspoint - c2 ;// -Pcrosspoint);
		gravity = 0;
		// 방향 : (crosspoint - p4); 위로 방향
		// 크기 : (crosspoint - bottom)
		return true;
	}
	return false; // 충돌 하지 않음.
}


void Player::Move() 
{
	// if (OnGround)		// 땅이면
	// 	mVelo.y = 0.0f;
	// else               // 땅이 아니면 
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

	// OnGround 조건 &&로 추가 
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
	// player 바닥이 다른 sprite의 Top과 맞닿으면 y축 속도는 0이 된다. 
	if((- Bottom + (g_Extern.WINDOWSIZE_HEIGHT - (other.mPos.y + other.mSize.y / 2)) <= 0.1)
		&& (Right > (other.mPos.x - other.mSize.x / 2))
		&& (Left < (other.mPos.x + other.mSize.x / 2))) OnGround = true;
	else OnGround = false;
}