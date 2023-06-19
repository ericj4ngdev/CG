#include "Include.h"
DWORD startTime = 0; // ���� �ð��� �����ϴ� ����

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

	isinc = true;
	isDown = false;
	keydownCount = 0;
	count = 0;
	direction = 1;
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


	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x * direction, mSize.y, 1);
	
	Controller();

	// �߶� �־�� �ϴµ�...
	// DrawBox(1);

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
		startTime = GetTickCount64();     // ���� ����
		isIdle = false;
		isWalk = true;
		isDown = true;
	}
	else isIdle = true;

	if (KeyDown(VK_LEFT) && !isDown)
	{
		direction = -1;
		// glScalef(mSize.x, mSize.y, 1);
		startTime = GetTickCount64();     // ���� ����
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

	DWORD currentTime = GetTickCount64();         // �ý��� �ð� 

	// ������ ����
	if (isDown)
	{
		// �ִϸ��̼� ��ȯ��
		if ((currentTime - startTime) >= 120)     // 0.2��
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

	// ����� Scale �ִ� �κ� 
	// ���߿� ĳ���� ���� �ً�, x��ǥ ��ȣ �ݴ�� �ϸ� �ɵ�... 
	// v[0][0] = v[1][0] = v[2][0] = v[3][0] = size / 2;
	// v[4][0] = v[5][0] = v[6][0] = v[7][0] = -size / 2;
	// v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;
	// v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1.5;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -0.5;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 0.5;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -0.5;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = 0.5;

	int i = 5;
	glBegin(GL_POLYGON);
	glNormal3fv(&n[i][0]);					// ���� ���� ���� ���͸� ����
	if (x == 2) // ä��
	{	
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -2.5;

		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 0.5;
		// �ڸ� ��ġ ����
		glTexCoord2f(92 / 433.0, 1 - (154 / 742.0));     glVertex3fv(&v[faces[i][0]][0]);      // ���� �Ʒ�    
		glTexCoord2f(92 / 433.0, 1 - (186 / 742.0));     glVertex3fv(&v[faces[i][1]][0]);      // ���� ��
		glTexCoord2f(142 / 433.0, 1 - (186 / 742.0));    glVertex3fv(&v[faces[i][2]][0]);       // ������ ��
		glTexCoord2f(142 / 433.0, 1 - (154 / 742.0));    glVertex3fv(&v[faces[i][3]][0]);       // ������ �Ʒ�
	}
	else
	{
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1.5;
		glTexCoord2f((1 + 40 * x) / 433.0, 1 - (154 / 742.0));    glVertex3fv(&v[faces[i][0]][0]);      // ���� �Ʒ�    
		glTexCoord2f((1 + 40 * x) / 433.0, 1 - (186 / 742.0));    glVertex3fv(&v[faces[i][1]][0]);      // ���� ��
		glTexCoord2f((33 + 40 * x) / 433.0, 1 - (186 / 742.0));   glVertex3fv(&v[faces[i][2]][0]);        // ������ ��
		glTexCoord2f((33 + 40 * x) / 433.0, 1 - (154 / 742.0));   glVertex3fv(&v[faces[i][3]][0]);        // ������ �Ʒ�
	}

	glEnd();
}	

void Player::InputAttackKey() {
	if ((KeyDown('Z') || KeyDown('z')) && !isDown)
	{
		// mPos.x = mPos.x - 10;
		startTime = GetTickCount64();      // ���� ����
		isIdle = false;
		isAttack = true;
		isDown = true;		
	}
	else isIdle = true;

	// �Է� �����ڵ�
	if (!(KeyDown('Z') || KeyDown('z')))
	{
		count = 0;
	}

	DWORD currentTime = GetTickCount64();
	int gap = currentTime - startTime;
	// 0.2�� �ڿ� ���� ��� ���
	// ������ ���� isDown�� true�̹Ƿ� ������ ���ȿ��� ���
	if (isDown)
	{
		// printf("c : %d   s : %d ���� : %d \n", currentTime, startTime, currentTime - startTime);
		// �ִϸ��̼� ��ȯ��
		if (gap >= 100)     // 0.2�ʵ��� ��� �����ؼ� ������ƽ�� �Ǿ���..
		{
			if (count == 0) count++;
		}
		if (gap >= 200) {
			if (count == 1) count++;
		}
		// 0.6�� �ڿ� false�� �ٲ������ν� �ѹ� ������ �ڵ����� 3����� ����ǰ� ��
		if (gap >= 400)
		{
			if (count == 2) count = 0;
			isDown = false;
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

	glTexCoord2f(250 / 433.0, 1 - (118 / 742.0));    glVertex3fv(&v[faces[i][0]][0]);      // ���� �Ʒ�    
	glTexCoord2f(250 / 433.0, 1 - (142 / 742.0));	   glVertex3fv(&v[faces[i][1]][0]);      // ���� ��
	glTexCoord2f(266 / 433.0, 1 - (142 / 742.0));   glVertex3fv(&v[faces[i][2]][0]);        // ������ ��
	glTexCoord2f(266 / 433.0, 1 - (118 / 742.0));   glVertex3fv(&v[faces[i][3]][0]);        // ������ �Ʒ�

	glEnd();
}

void Player::InputJumpKey() {
	// ������ ����
	if (isDown)
	{
		// �� ���� ������� ����
		// OnGround = false�̸� jump��� ���		
		std::cout << "InputJumpKey, if�� �� " << OnGround << '\n';		// 1
		if (OnGround) 
		{
			isDown = false;		// �����ϸ� false�Ǽ� �ٽ� �Է� ����
			isJump = false;		// switch������ IDLE�� �ٲ�. �ٵ� ���� ��� �����ϰ� �����Ѵ�. 	
			// �̰� ����� ���ִ� ���·� ������. �ֱ׷��� ���� ��. ����... 
			// ��� ������ �ִٸ� isDown�� �ذ��ؾ� �ϴµ� �׷��� ���Ѵ�. isDown�� false�� �Ǹ� �Է��� ���������� �� ���������� �� ���̴�. 
			// �װ� ����
			// �� ���� �����ڰ�??
			std::cout << "InputJumpKey, if�� �� " << OnGround << '\n';		// 1
		}
		Jump();
	}

	// if (!KeyDown(VK_SPACE)) isDown = false;

	//������ ������ T && F
	if (KeyDown(VK_SPACE) && !isDown)
	{
		isJump = true;
		isDown = true;
		std::cout << "InputJumpKey, ù���� if�� " << OnGround << '\n';		// 0
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

void Player::Controller()
{
	// printf("%d", currentState);
	// printf("%d", count);
	switch (currentState) {
		case IDLE:
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

void Player::Move()
{
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

	// �� ���� ���� & space => ����
	if (KeyDown(VK_SPACE) && OnGround) {
		currentState = JUMP;
		JumpPower = 15;
		// OnGround = false;
	}
	if (KeyDown('Z') || KeyDown('z'))
	{
		currentState = ATTACK;
		// isAttack = true;
	}

	if (KeyDown(VK_DOWN))
	{
		currentState = SIT;
	}
	
}

void Player::Attack() 
{
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	glBindTexture(GL_TEXTURE_2D, m_Texid);
	// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

	// ������ ������ �����ϴ� �Լ�
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ

	glTranslatef(mPos.x + 150, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x * 4, mSize.y / 4, 1);

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
}

//void Player::IsGround(Sprite& other) 
//{
//	// player �ٴ��� �ٸ� sprite�� Top�� �´����� y�� �ӵ��� 0�� �ȴ�. 
//	if (other.Top - Bottom <= 0.1f) OnGround = true;
//	else OnGround = false;
//} 