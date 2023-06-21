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
	attackRange = 0;
	loadTexture();
}

// 이미지 로드하고 텍스쳐 입히기
void Player::initTexture(const char *name) {
	mPos = Vector2D(150, 850/2-100);		// 초기위치
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
	isJump = true;
	isSit = true;

	isKeyDown = false;
	isinc = true;
	attackRange = 0;
	keydownCount = 0;
	count = 0;
	direction = 1;
}

void Player::Transform()
{
	// printf("%f , %f  ", mPos.x, mPos.y);
	mTop = mPos.y - mSize.y / 2;
	mBottom = mPos.y + mSize.y / 2;
	mRight = mPos.x + mSize.x / 2;
	mLeft = mPos.x - mSize.x / 2;

	vLT = Vector2D(mLeft, mTop);
	vRT = Vector2D(mRight, mTop);
	vRB = Vector2D(mRight, mBottom);
	vLB = Vector2D(mLeft, mBottom);
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
	glScalef(-mSize.x * direction, mSize.y, 1);
	
	StateMachine();

	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수

	// printf("%s \n", this->OnGround ? "true" : "false");
	// if (isAttack) {
	// 	DWORD currentTime = GetTickCount64(); // 현재 시간 측정
	// 
	// 	// 경과 시간이 0.25초가 되면 사각형 그리기 중단
	// 	if ((currentTime - startTime) >= 500)
	// 		isAttack = false;
	// 
	// 	Attack();
	// }
}

bool Player::Collide(Sprite other)
{
	if ((mRight >= other.mLeft)
		&& (mLeft <= other.mRight)
		&& (mBottom >= other.mTop)
		&& (mTop <= other.mBottom))
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
		glTexCoord2f(8 / 433.0, 1 - (114 / 742.0)); 	glVertex3fv(&v[faces[i][0]][0]);		// 왼쪽 아래		(0,1) 
		glTexCoord2f(8 / 433.0, 1 - (146 / 742.0));		glVertex3fv(&v[faces[i][1]][0]);		// 왼쪽 위		(0,0)
		glTexCoord2f(24 / 433.0, 1 - (146 / 742.0));	glVertex3fv(&v[faces[i][2]][0]);		// 오른쪽 위		(1,0)
		glTexCoord2f(24 / 433.0, 1 - (114 / 742.0));	glVertex3fv(&v[faces[i][3]][0]);		// 오른쪽 아래	(1,1)

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
	if (KeyDown(VK_RIGHT) && !isKeyDown)
	{
		direction = 1;
		startTime = GetTickCount64();     // 누른 시점
		isIdle = false;
		isWalk = true;
		isKeyDown = true;
	}
	else isIdle = true;

	if (KeyDown(VK_LEFT) && !isKeyDown)
	{
		direction = -1;
		// glScalef(mSize.x, mSize.y, 1);
		startTime = GetTickCount64();     // 누른 시점
		isIdle = false;
		isWalk = true;
		isKeyDown = true;
	}
	else isIdle = true;

	// 입력 종료
	if (!(KeyDown(VK_RIGHT) || KeyDown(VK_LEFT)))
	{ 
		isWalk = false; 
		isIdle = true;  
		isKeyDown = false;  
		count = 0;
	}

	DWORD currentTime = GetTickCount64();         // 시스템 시간 

	// 눌리면 실행
	if (isKeyDown)
	{
		// 애니메이션 전환부
		if ((currentTime - startTime) >= 120)     // 0.2초
		{
			if (count == 0) { isinc = true; }
			if (count == 2) { isinc = false; }
			if (isinc) count++;
			else count--;
			// 전환 후, 다시 입력 가능
			isKeyDown = false;
		}
	}
	// 눌렸다면 0.2초간 startTime 은 고정    

	Walk(count);
}

void Player::Attack(int x)
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

	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -0.5;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 0.5;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -0.5;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = 0.5;

	int i = 5;
	glBegin(GL_POLYGON);
	glNormal3fv(&n[i][0]);					// 현재 면의 법선 벡터를 설정
	if (x == 2) // 채찍
	{	
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -2.5;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 0.5;
		// 자를 위치 조정
		glTexCoord2f(92 / 433.0, 1 - (154 / 742.0));     glVertex3fv(&v[faces[i][0]][0]);      // 왼쪽 아래    
		glTexCoord2f(92 / 433.0, 1 - (186 / 742.0));     glVertex3fv(&v[faces[i][1]][0]);      // 왼쪽 위
		glTexCoord2f(142 / 433.0, 1 - (186 / 742.0));    glVertex3fv(&v[faces[i][2]][0]);       // 오른쪽 위
		glTexCoord2f(142 / 433.0, 1 - (154 / 742.0));    glVertex3fv(&v[faces[i][3]][0]);       // 오른쪽 아래
	}
	else
	{
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1.5;
		glTexCoord2f((1 + 40 * x) / 433.0, 1 - (154 / 742.0));    glVertex3fv(&v[faces[i][0]][0]);      // 왼쪽 아래    
		glTexCoord2f((1 + 40 * x) / 433.0, 1 - (186 / 742.0));    glVertex3fv(&v[faces[i][1]][0]);      // 왼쪽 위
		glTexCoord2f((33 + 40 * x) / 433.0, 1 - (186 / 742.0));   glVertex3fv(&v[faces[i][2]][0]);        // 오른쪽 위
		glTexCoord2f((33 + 40 * x) / 433.0, 1 - (154 / 742.0));   glVertex3fv(&v[faces[i][3]][0]);        // 오른쪽 아래
	}

	glEnd();
}	

void Player::InputAttackKey() {
	if ((KeyDown('Z') || KeyDown('z')) && !isKeyDown)
	{
		// mPos.x = mPos.x - 10;
		startTime = GetTickCount64();      // 누른 시점
		isIdle = false;
		isAttack = true;
		isKeyDown = true;		
	}
	else isIdle = true;

	// 입력 종료코드
	if (!(KeyDown('Z') || KeyDown('z')))
	{
		count = 0;
	}

	DWORD currentTime = GetTickCount64();
	int gap = currentTime - startTime;
	// 0.2초 뒤에 다음 장면 재생
	// 누르는 동안 isDown은 true이므로 누르는 동안에만 재생
	if (isKeyDown)
	{
		// printf("c : %d   s : %d 차이 : %d \n", currentTime, startTime, currentTime - startTime);
		// 애니메이션 전환부
		if (gap >= 100)     // 0.2초동안 계속 증가해서 슬랩스틱이 되었다..
		{
			if (count == 0) count++;
		}
		if (gap >= 200) {
			if (count == 1) count++;
		}
		// 0.6초 뒤에 false로 바꿔줌으로써 한번 누르면 자동으로 3장면이 재생되게 함
		if (gap >= 400)
		{
			if (count == 2) count = 0;
			isKeyDown = false;
			isAttack = false;
		}
	}
	Attack(count);
}

void Player::Jump()
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

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 0.5;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -0.5;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 0.16;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -0.5;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = 0.5;

	int i = 5;
	glBegin(GL_POLYGON);
	glNormal3fv(&n[i][0]);

	glTexCoord2f(250 / 433.0, 1 - (118 / 742.0));    glVertex3fv(&v[faces[i][0]][0]);      // 왼쪽 아래    
	glTexCoord2f(250 / 433.0, 1 - (142 / 742.0));	   glVertex3fv(&v[faces[i][1]][0]);      // 왼쪽 위
	glTexCoord2f(266 / 433.0, 1 - (142 / 742.0));   glVertex3fv(&v[faces[i][2]][0]);        // 오른쪽 위
	glTexCoord2f(266 / 433.0, 1 - (118 / 742.0));   glVertex3fv(&v[faces[i][3]][0]);        // 오른쪽 아래

	glEnd();
}

void Player::InputJumpKey() {
	// 누르고서 반응
	if (isKeyDown)
	{
		// 땅 위면 점프모션 해제
		// OnGround = false이면 jump모션 재생		
		// std::cout << "InputJumpKey, if문 밖 " << OnGround << '\n';		// 1
		if (OnGround) 
		{
			isKeyDown = false;		// 착지하면 false되서 다시 입력 가능
			isJump = false;		// switch문에서 IDLE로 바뀜. 	
			// 이거 지우면 서있는 상태로 점프함. 왜그런지 나도 모름. 씨발... 
			// 계속 누르고 있다면 isDown이 해결해야 하는데 그러지 못한다. 
			// 그게 문제
			// 또 변수 만들자고??
			// std::cout << "InputJumpKey, if문 안 " << OnGround << '\n';		// 1
		}
		Jump();
	}

	// if (!KeyDown(VK_SPACE)) isDown = false;

	//누르고 있으면 T && F
	if (KeyDown(VK_SPACE) && !isKeyDown)
	{
		isJump = true;
		isKeyDown = true;
		// std::cout << "InputJumpKey, 첫번쨰 if문 " << OnGround << '\n';		// 0
		Jump();
	}
}

void Player::Sit()
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

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 0.5;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -0.5;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 0.16;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -0.5;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = 0.5;

	int i = 5;
	glBegin(GL_POLYGON);
	glNormal3fv(&n[i][0]);

	glTexCoord2f(250 / 433.0, 1 - (119 / 742.0));    glVertex3fv(&v[faces[i][0]][0]);      // 왼쪽 아래    
	glTexCoord2f(250 / 433.0, 1 - (142 / 742.0));	   glVertex3fv(&v[faces[i][1]][0]);      // 왼쪽 위
	glTexCoord2f(266 / 433.0, 1 - (142 / 742.0));   glVertex3fv(&v[faces[i][2]][0]);        // 오른쪽 위
	glTexCoord2f(266 / 433.0, 1 - (119 / 742.0));   glVertex3fv(&v[faces[i][3]][0]);        // 오른쪽 아래

	glEnd();
}

void Player::InputSitKey() {
	if (KeyDown(VK_DOWN))
	{
		isIdle = false;
		isSit = true;
		Sit();
	}
	else isIdle = true;

	if (!KeyDown(VK_DOWN)) { isSit = false; }
}

void Player::StateMachine()
{
	// printf("%d", currentState);
	// printf("%d", count);
	switch (currentState) {
		case IDLE:
			attackRange = 0;
			Idle();
			break;
		case WALK:
			InputWalkKey();
			if (!isWalk) 
			{
				currentState = IDLE;
			}
			break;
		case ATTACK:
			InputAttackKey();
			DrawCollide();
			if (!isAttack) 
			{
				currentState = IDLE;
			}
			break;
		case JUMP:
			InputJumpKey();
			if (!isJump) 
			{
				currentState = IDLE;
			}
			break;
		case SIT:
			InputSitKey();
			if (!isSit) 
			{
				currentState = IDLE;
			}
			break;
		default:
			std::cout << "Invalid state" << std::endl;
			break;
	}
}

void Player::InputController()
{
	mPos.y += gravity - JumpPower;
	if (JumpPower > 0)
		JumpPower -= 0.5f;		// 매 프레임마다 순차적으로 뺴준다. 
	else
		JumpPower = 0;

	if (KeyDown(VK_LEFT))
	{
		currentState = WALK;
		mPos.x -= mVelo.x;		
	}

	if (KeyDown(VK_RIGHT))
	{
		currentState = WALK;
		mPos.x += mVelo.x;
	}

	// 땅 위에 있음 & space => 점프
	// printf("%d", OnGround);
	if (KeyDown(VK_SPACE) && OnGround) {
		currentState = JUMP;
		JumpPower = 15;
	}
	if (KeyDown('Z') || KeyDown('z'))
	{
		currentState = ATTACK;
		attackRange = 100;
	}

	if (KeyUp('Z') || KeyUp('z'))
	{
		attackRange = 0;
	}

	if (KeyDown(VK_DOWN))
	{
		currentState = SIT;
	}
	
}

void Player::DrawCollide()
{
	// 그리기
	glPushMatrix();			// 현재 모델뷰 행렬을 스택에 저장하는 함수
	glBindTexture(GL_TEXTURE_2D, NULL);
	// 현재 활성화된 텍스처 유닛에 2D 텍스처를 바인딩하는 함수

	// 현재의 색상을 설정하는 함수
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

	glMatrixMode(GL_MODELVIEW);			// 현재의 행렬 모드를 설정하는 함수
	glLoadIdentity();					// 현재 행렬을 단위 행렬로 초기화

	glTranslatef(mPos.x + 100, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(attackRange, mSize.y / 4, 1);

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// 텍스처 언바인딩
	glPopMatrix();			// 스택에 저장된 이전의 모델뷰 행렬을 복원하는 함수
	// 충돌

}

void Player::DrawCollide(Sprite& other)
{
	Vector2D weaponPos(mPos.x + 100, mPos.y);
	Vector2D weaponSize(0, mSize.y / 4);
	weaponPos.print();

	float Top = weaponPos.y - weaponSize.y / 2;
	float Bottom = weaponPos.y + weaponSize.y / 2;
	float Right = weaponPos.x + weaponSize.x / 2;
	float Left = weaponPos.x - weaponSize.x / 2;

	// printf("%d \n", attackRange);
	// 충돌
	if ((Right >= other.mLeft)
		&& (Left <= other.mRight)
		&& (Bottom >= other.mTop)
		&& (Top <= other.mBottom))
	{
		other.Release();			// 텍스처 초기화.
		other.mColor.a = 0;			// 투명화
	}	
}

//void Player::IsGround(Sprite& other) 
//{
//	// player 바닥이 다른 sprite의 Top과 맞닿으면 y축 속도는 0이 된다. 
//	if (other.Top - Bottom <= 0.1f) OnGround = true;
//	else OnGround = false;
//} 