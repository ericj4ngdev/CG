#include "Include.h"
// DWORD startTime = 0; // ���� �ð��� �����ϴ� ����
DWORD currentTime = 0;
DWORD start = 0;
int gap = 0;
void Player::initPos() {
	mPos = Vector2D(150, 850/2);		// �ʱ���ġ
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

// �̹��� �ε��ϰ� �ؽ��� ������
void Player::initTexture(const char *name) {
	mPos = Vector2D(150, 850/2-100);		// �ʱ���ġ
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
	isDown = false;
	isAttackKeyDown = false;

	isKeyDown = false;
	isinc = true;
	attackRange = 0;
	
	count = 0;
	direction = 1;
}

void Player::Transform()
{
	printf("%f , %f  \n", mPos.x, mPos.y);
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
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	glBindTexture(GL_TEXTURE_2D, m_Texid);
	// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

	// ������ ������ �����ϴ� �Լ�
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ


	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x * direction, mSize.y, 1);
	
	StateMachine();

	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�

	// printf("%s \n", this->OnGround ? "true" : "false");
	// if (isAttack) {
	// 	DWORD currentTime = GetTickCount64(); // ���� �ð� ����
	// 
	// 	// ��� �ð��� 0.25�ʰ� �Ǹ� �簢�� �׸��� �ߴ�
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
	return false; // �浹 ���� ����.
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

	// ���߿� ĳ���� ���� �ً�, x��ǥ ��ȣ �ݴ�� �ϸ� �ɵ�... 
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
		glNormal3fv(&n[i][0]);					// ���� ���� ���� ���͸� ����

		// �ؽ�ó ��ǥ ����		// ���� ��ǥ�� ����. ��׸���
		glTexCoord2f(8 / 433.0, 1 - (114 / 742.0)); 	glVertex3fv(&v[faces[i][0]][0]);		// ���� �Ʒ�		(0,1) 
		glTexCoord2f(8 / 433.0, 1 - (146 / 742.0));		glVertex3fv(&v[faces[i][1]][0]);		// ���� ��		(0,0)
		glTexCoord2f(24 / 433.0, 1 - (146 / 742.0));	glVertex3fv(&v[faces[i][2]][0]);		// ������ ��		(1,0)
		glTexCoord2f(24 / 433.0, 1 - (114 / 742.0));	glVertex3fv(&v[faces[i][3]][0]);		// ������ �Ʒ�	(1,1)

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

	// ���߿� ĳ���� ���� �ً�, x��ǥ ��ȣ �ݴ�� �ϸ� �ɵ�... 
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
	glNormal3fv(&n[i][0]);					// ���� ���� ���� ���͸� ����

	// �ؽ�ó ��ǥ ����		// ���� ��ǥ�� ����. ��׸���
	glTexCoord2f((8 + 40 * x) / 433.0,  1 - (115 / 742.0)); 	glVertex3fv(&v[faces[i][0]][0]);	
	glTexCoord2f((8 + 40 * x) / 433.0,  1 - (146 / 742.0));		glVertex3fv(&v[faces[i][1]][0]);	
	glTexCoord2f((25 + 40 * x) / 433.0, 1 - (146 / 742.0));		glVertex3fv(&v[faces[i][2]][0]);	
	glTexCoord2f((25 + 40 * x) / 433.0, 1 - (115 / 742.0));		glVertex3fv(&v[faces[i][3]][0]);	

	glEnd();
}

void Player::InputWalkKey()
{
	
	// ��ó���� isDown�� false�̾ �Է� ����
	if (KeyDown(VK_RIGHT) && !isDown)
	{
		direction = 1;
		start = GetTickCount64();     // ���� ����
		isIdle = false;
		isWalk = true;
		isDown = true;
	}
	else isIdle = true;

	if (KeyDown(VK_LEFT) && !isDown)
	{
		direction = -1;
		// glScalef(mSize.x, mSize.y, 1);
		start = GetTickCount64();     // ���� ����
		isIdle = false;
		isWalk = true;
		isDown = true;
	}
	else isIdle = true;

	// �Է� ����
	if (!(KeyDown(VK_RIGHT) || KeyDown(VK_LEFT)))
	{ 
		isWalk = false; 
		isIdle = true;  
		isDown = false;
		count = 0;
	}

	// DWORD currentTime = GetTickCount64();         // �ý��� �ð� 

	// ������ ����
	if (isDown)
	{
		// �ִϸ��̼� ��ȯ��
		if ((currentTime - start) >= 120)     // 0.2��
		{
			if (count == 0) { isinc = true; }
			if (count == 2) { isinc = false; }
			if (isinc) count++;
			else count--;
			// ��ȯ ��, �ٽ� �Է� ����
			isDown = false;
		}
	}
	// ���ȴٸ� 0.2�ʰ� startTime �� ����    

	Walk(count);
}

void Player::Attack()
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

	// �������Ӹ��� üũ
	DWORD currentTime = GetTickCount64();
	int gap = currentTime - startTime;
	printf("c : %d   s : %d ���� : %d \n", currentTime, startTime, currentTime - startTime);
	int i = 5;
	glBegin(GL_POLYGON);
	glNormal3fv(&n[i][0]);

	if (gap >= 100)
	{
		if (count == 0) count++;
		else { count = 0; count++; }
	}
	if (gap >= 200) { count++;  }
	if (gap >= 400)
	{
		// ���ڸ�
		isAttackKeyDown = false;
		isAttack = false;
	}

	if (count == 2) // ä��
	{
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -2.5;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 0.5;
		// �ڸ� ��ġ ����
		glTexCoord2f(92 / 433.0, 1 - (154 / 742.0));     glVertex3fv(&v[faces[i][0]][0]); 
		glTexCoord2f(92 / 433.0, 1 - (186 / 742.0));     glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(142 / 433.0, 1 - (186 / 742.0));    glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(142 / 433.0, 1 - (154 / 742.0));    glVertex3fv(&v[faces[i][3]][0]);
	}
	else
	{
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1.5;
		glTexCoord2f((1 + 40 * count) / 433.0, 1 - (154 / 742.0));    glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f((1 + 40 * count) / 433.0, 1 - (186 / 742.0));    glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f((33 + 40 * count) / 433.0, 1 - (186 / 742.0));   glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f((33 + 40 * count) / 433.0, 1 - (154 / 742.0));   glVertex3fv(&v[faces[i][3]][0]);
	}


	glEnd();
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

	glTexCoord2f(250 / 433.0, 1 - (118 / 742.0));    glVertex3fv(&v[faces[i][0]][0]);      // ���� �Ʒ�    
	glTexCoord2f(250 / 433.0, 1 - (142 / 742.0));	   glVertex3fv(&v[faces[i][1]][0]);      // ���� ��
	glTexCoord2f(266 / 433.0, 1 - (142 / 742.0));   glVertex3fv(&v[faces[i][2]][0]);        // ������ ��
	glTexCoord2f(266 / 433.0, 1 - (118 / 742.0));   glVertex3fv(&v[faces[i][3]][0]);        // ������ �Ʒ�

	glEnd();
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

	glTexCoord2f(250 / 433.0, 1 - (119 / 742.0));    glVertex3fv(&v[faces[i][0]][0]);      // ���� �Ʒ�    
	glTexCoord2f(250 / 433.0, 1 - (142 / 742.0));	   glVertex3fv(&v[faces[i][1]][0]);      // ���� ��
	glTexCoord2f(266 / 433.0, 1 - (142 / 742.0));   glVertex3fv(&v[faces[i][2]][0]);        // ������ ��
	glTexCoord2f(266 / 433.0, 1 - (119 / 742.0));   glVertex3fv(&v[faces[i][3]][0]);        // ������ �Ʒ�

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
	switch (currentState) 
	{
		case IDLE:
			attackRange = 0;
			Idle();
			break;
		case WALK:
			InputWalkKey();
			if (!isWalk) { currentState = IDLE; }
			break;
		case ATTACK:
			Attack();
			if (!isAttack) { currentState = IDLE; }
			break;
		case JUMP:
			Jump();
			if (!isJump) { currentState = IDLE; }
			break;
		case SIT:
			InputSitKey();
			if (!isSit) { currentState = IDLE; }
			break;
		default:
			std::cout << "Invalid state" << std::endl;
			break;
	}
}

void Player::InputController()
{	
	DWORD currentTime = GetTickCount64();		// ��� ����
	gap = currentTime - startTime;	// �ð� ���	

	mPos.y += gravity - JumpPower;
	if (JumpPower > 0)
		JumpPower -= 0.5f;		// �� �����Ӹ��� ���������� ���ش�. 
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

	// ����
	if (OnGround) isJump = false;
	if (!OnGround) currentState = JUMP;			// �����̸� �������¸�� ����
	if (KeyDown(VK_SPACE) && OnGround)
	{
		if (isKeyDown)		// ����� �� �����°�? = isAttack�� false�ΰ�
		{
			currentState = JUMP;
			JumpPower = 15;
			isKeyDown = false;
			isJump = true;
		}
	}
	if (KeyUp(VK_SPACE)) 
	{
		isKeyDown = true;
		isJump = false;
	}

	// ����
	if (KeyDown('Z'))
	{
		// ���� ������ true, ������ false
		if (isAttackKeyDown)
		{
			currentState = ATTACK;
			startTime = GetTickCount64();
			attackRange = 100;
			isAttackKeyDown = false;		
			isAttack = true;
		}
	}
	// ���� true
	if (KeyUp('Z')) {
		isAttackKeyDown = true;
		isAttack = false;
		attackRange = 0;
		count = 0;
	}
	// 1�� �Ŀ� ��� 
	if (gap <= 400) currentState = ATTACK;
	else isAttack = false;		// 0.4�� �Ŀ� ����


	if (KeyDown(VK_DOWN))
	{
		currentState = SIT;
	}
	
}

void Player::DrawCollide()
{
	// �׸���
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	glBindTexture(GL_TEXTURE_2D, NULL);
	// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

	// ������ ������ �����ϴ� �Լ�
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ

	glTranslatef(mPos.x + 100, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(attackRange, mSize.y / 4, 1);

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
	// �浹

}

void Player::DrawCollide(Sprite& other)
{
	Vector2D weaponPos(mPos.x + 100, mPos.y);
	Vector2D weaponSize(0, mSize.y / 4);
	// weaponPos.print();

	float Top = weaponPos.y - weaponSize.y / 2;
	float Bottom = weaponPos.y + weaponSize.y / 2;
	float Right = weaponPos.x + weaponSize.x / 2;
	float Left = weaponPos.x - weaponSize.x / 2;

	// printf("%d \n", attackRange);
	// �浹
	if ((Right >= other.mLeft)
		&& (Left <= other.mRight)
		&& (Bottom >= other.mTop)
		&& (Top <= other.mBottom))
	{
		other.Release();			// �ؽ�ó �ʱ�ȭ.
		other.mColor.a = 0;			// ����ȭ
	}	
}

//void Player::IsGround(Sprite& other) 
//{
//	// player �ٴ��� �ٸ� sprite�� Top�� �´����� y�� �ӵ��� 0�� �ȴ�. 
//	if (other.Top - Bottom <= 0.1f) OnGround = true;
//	else OnGround = false;
//} 