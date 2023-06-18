#include "Include.h"
DWORD startTime = 0; // 시작 시간을 저장하는 변수

void Player::initPos() {
	mPos = Vector2D(150, 850/2);		// 초기위치
	mVelo = Vector2D(3, 3);
	mSize = Vector2D(50, 100);
	m_Texid = NULL;
	mColor = Color4f(1, 1, 1, 1);
	gravity = 5;
	OnGround = false;
	OnCollide = false;
	JumpPower = 0;
	MoveSpeed = 2.0f;
	isAttack = false;
	loadTexture();
}

// 이미지 로드하고 텍스쳐 입히기
void Player::initTexture(const char *name) {
	mPos = Vector2D(150, 850/2);		// 초기위치
	mVelo = Vector2D(2, 2);
	mSize = Vector2D(50, 100);
	
	m_Tex.LoadImage(name);
	m_Texid = NULL;
	m_Texid = *m_Tex.GetTexture();

	mColor = Color4f(1, 1, 1, 1);
	gravity = 5;
	OnGround = false;
	OnCollide = false;
	JumpPower = 0;
	MoveSpeed = 2.0f;
	isIdle = true;
	isWalk = true;
	isAttack = true;
	isinc = true;
	isDown = false;
	count = 0;
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


	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x, mSize.y, 1);
	Controller();

	// 잘라 넣어야 하는데...
	// DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수

	if (isAttack) {
		DWORD currentTime = GetTickCount64(); // 현재 시간 측정

		// 경과 시간이 0.25초가 되면 사각형 그리기 중단
		if ((currentTime - startTime) >= 500)
			isAttack = false;

		Attack();
	}
}

bool Player::Collide(Sprite other)
{
	// 축 검사해서 겹치면 
	// bottom > other.top (일반 좌표)
	// 실시간이라 변수로 계산 X
	if ((Right >= other.Left)
		&& (Left <= other.Right)
		&& (Bottom >= other.Top)
		&& (Top <= other.Bottom))
	{
		OnCollide = true;
		return true;
	}
	OnCollide = false;
	return false; // 충돌 하지 않음.
}

void Player::Idle()
{
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	GLfloat v[8][3];

	// 나중에 캐릭터 반전 줄떄, x좌표 부호 반대로 하면 될듯... 
	// v[0][0] = v[1][0] = v[2][0] = v[3][0] = size / 2;
	// v[4][0] = v[5][0] = v[6][0] = v[7][0] = -size / 2;
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;	
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 0.5;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -0.5;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 0.5;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -0.5;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = 0.5;

	//for (int i = 0; i < 6; i++)
	//{
	int i = 5;
		glBegin(GL_POLYGON);
		glNormal3fv(&n[i][0]);					// 현재 면의 법선 벡터를 설정

		// 텍스처 좌표 설정		// 정점 좌표를 설정. 면그리기
		glTexCoord2f(8 / 433.0, 1 - (115 / 742.0)); 	glVertex3fv(&v[faces[i][0]][0]);		// 왼쪽 아래		(0,1) 
		glTexCoord2f(8 / 433.0, 1 - (146 / 742.0)); glVertex3fv(&v[faces[i][1]][0]);			// 왼쪽 위		(0,0)
		glTexCoord2f(25 / 433.0, 1 - (146 / 742.0));	glVertex3fv(&v[faces[i][2]][0]);		// 오른쪽 위		(1,0)
		glTexCoord2f(25 / 433.0, 1 - (115 / 742.0));		glVertex3fv(&v[faces[i][3]][0]);	// 오른쪽 아래	(1,1)

		glEnd();
	
}

void Player::Walk(int x) {

	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	GLfloat v[8][3];

	// 나중에 캐릭터 반전 줄떄, x좌표 부호 반대로 하면 될듯... 
	// v[0][0] = v[1][0] = v[2][0] = v[3][0] = size / 2;
	// v[4][0] = v[5][0] = v[6][0] = v[7][0] = -size / 2;
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 0.5;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -0.5;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 0.5;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -0.5;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = 0.5;

	int i = 5;
	glBegin(GL_POLYGON);
	glNormal3fv(&n[i][0]);					// 현재 면의 법선 벡터를 설정

	// 텍스처 좌표 설정		// 정점 좌표를 설정. 면그리기
	glTexCoord2f((8 + 40 * x) / 433.0,  1 - (115 / 742.0)); 	glVertex3fv(&v[faces[i][0]][0]);	
	glTexCoord2f((8 + 40 * x) / 433.0,  1 - (146 / 742.0));		glVertex3fv(&v[faces[i][1]][0]);	
	glTexCoord2f((25 + 40 * x) / 433.0, 1 - (146 / 742.0));		glVertex3fv(&v[faces[i][2]][0]);	
	glTexCoord2f((25 + 40 * x) / 433.0, 1 - (115 / 742.0));		glVertex3fv(&v[faces[i][3]][0]);	

	glEnd();
}

void Player::InputWalkKey()
{
	// 맨처음엔 isDown이 false이어서 입력 가능
	if (KeyDown(VK_RIGHT) && !isDown)
	{
		startTime = GetTickCount64();     // 누른 시점
		isIdle = false;
		isWalk = true;
		isDown = true;
	}
	else isIdle = true;

	// 입력 종료
	if (!KeyDown(VK_RIGHT)) { isWalk = false; isIdle = true;  isDown = false;  count = 0;}

	DWORD currentTime = GetTickCount64();         // 시스템 시간 

	// 눌리면 실행
	if (isDown)
	{
		// 애니메이션 전환부
		if ((currentTime - startTime) >= 150)     // 0.2초
		{
			if (count == 0) { isinc = true; }
			if (count == 2) { isinc = false; }
			if (isinc) count++;
			else count--;
			// 전환 후, 다시 입력 가능
			isDown = false;
		}
	}
	// 눌렸다면 0.2초간 startTime 은 고정    

	Walk(count);
}


void Player::Attack(int x)
{
	glBegin(GL_POLYGON);
	if (x == 2) // 채찍
	{
		glTexCoord2d(92 / 433.0, 186 / 742.0);     glVertex3d(-0.5, -0.33, 0.0);      // 왼쪽 아래    
		glTexCoord2d(92 / 433.0, 153 / 742.0);     glVertex3d(-0.5, 0.33, 0.0);       // 왼쪽 위
		glTexCoord2d(142 / 433.0, 153 / 742.0);     glVertex3d(0.5, 0.33, 0.0);        // 오른쪽 위
		glTexCoord2d(142 / 433.0, 186 / 742.0);     glVertex3d(0.5, -0.33, 0.0);       // 오른쪽 아래
	}
	else
	{
		glTexCoord2d((1 + 40 * x) / 433.0, 186 / 742.0);     glVertex3d(-0.75, -0.33, 0.0);       // 왼쪽 아래    
		glTexCoord2d((1 + 40 * x) / 433.0, 153 / 742.0);     glVertex3d(-0.75, 0.33, 0.0);        // 왼쪽 위
		glTexCoord2d((33 + 40 * x) / 433.0, 153 / 742.0);     glVertex3d(-0.15, 0.33, 0.0);         // 오른쪽 위
		glTexCoord2d((33 + 40 * x) / 433.0, 186 / 742.0);     glVertex3d(-0.15, -0.33, 0.0);        // 오른쪽 아래
	}

	glEnd();
}

void Player::InputAttackKey() {

}


void Player::Controller()
{
	printf("%d", count);
	if (KeyDown(VK_RIGHT))
	{
		currentState = WALK;
	}
	if (KeyDown('Z') || KeyDown('z'))
	{
		currentState = ATTACK;
	}

	switch (currentState) {
	case IDLE:
		Idle();
		break;
	case WALK:
		InputWalkKey();
		if (!isWalk) {
			currentState = IDLE;
		}
		break;
	case ATTACK:
		// InputKey_2();
		// if (!isAttack) {
		// 	currentState = IDLE;
		// }
		break;
	default:
		std::cout << "Invalid state" << std::endl;
		break;
	}
}

void Player::Move()
{
	mPos.y += gravity - JumpPower;
	// std::cout << OnGround << '\n';
	if (JumpPower > 0)
		JumpPower -= 0.5f;		// 매 프레임마다 순차적으로 뺴준다. 
	else
		JumpPower = 0;

	if (KeyDown(VK_LEFT))
	{
		mPos.x -= mVelo.x;		
	}

	if (KeyDown(VK_RIGHT))
	{
		mPos.x += mVelo.x;
	}

	if (KeyDown(VK_SPACE) && OnGround)
		JumpPower = 15;
	

	if (KeyDown('Z') || KeyDown('z'))
	{
		isAttack = true;
	}

	if (KeyDown(VK_DOWN))
	{
		glScalef(mSize.x, mSize.y / 2, 1);
	}
	OnGround = false;
}



void Player::Attack() 
{
	glPushMatrix();			// 현재 모델뷰 행렬을 스택에 저장하는 함수
	glBindTexture(GL_TEXTURE_2D, m_Texid);
	// 현재 활성화된 텍스처 유닛에 2D 텍스처를 바인딩하는 함수

	// 현재의 색상을 설정하는 함수
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

	glMatrixMode(GL_MODELVIEW);			// 현재의 행렬 모드를 설정하는 함수
	glLoadIdentity();					// 현재 행렬을 단위 행렬로 초기화

	glTranslatef(mPos.x + 150, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x * 4, mSize.y / 4, 1);

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수
}

//void Player::IsGround(Sprite& other) 
//{
//	// player 바닥이 다른 sprite의 Top과 맞닿으면 y축 속도는 0이 된다. 
//	if (other.Top - Bottom <= 0.1f) OnGround = true;
//	else OnGround = false;
//} 