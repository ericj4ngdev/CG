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
	mPos = Vector2D(150, 850/2);		// �ʱ���ġ
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
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	glBindTexture(GL_TEXTURE_2D, m_Texid);
	// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

	// ������ ������ �����ϴ� �Լ�
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);

	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ


	glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
	glScalef(-mSize.x, mSize.y, 1);
	Controller();

	// �߶� �־�� �ϴµ�...
	// DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�

	if (isAttack) {
		DWORD currentTime = GetTickCount64(); // ���� �ð� ����

		// ��� �ð��� 0.25�ʰ� �Ǹ� �簢�� �׸��� �ߴ�
		if ((currentTime - startTime) >= 500)
			isAttack = false;

		Attack();
	}
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
		glTexCoord2f(8 / 433.0, 1 - (115 / 742.0)); 	glVertex3fv(&v[faces[i][0]][0]);		// ���� �Ʒ�		(0,1) 
		glTexCoord2f(8 / 433.0, 1 - (146 / 742.0)); glVertex3fv(&v[faces[i][1]][0]);			// ���� ��		(0,0)
		glTexCoord2f(25 / 433.0, 1 - (146 / 742.0));	glVertex3fv(&v[faces[i][2]][0]);		// ������ ��		(1,0)
		glTexCoord2f(25 / 433.0, 1 - (115 / 742.0));		glVertex3fv(&v[faces[i][3]][0]);	// ������ �Ʒ�	(1,1)

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
		startTime = GetTickCount64();     // ���� ����
		isIdle = false;
		isWalk = true;
		isDown = true;
	}
	else isIdle = true;

	// �Է� ����
	if (!KeyDown(VK_RIGHT)) { isWalk = false; isIdle = true;  isDown = false;  count = 0;}

	DWORD currentTime = GetTickCount64();         // �ý��� �ð� 

	// ������ ����
	if (isDown)
	{
		// �ִϸ��̼� ��ȯ��
		if ((currentTime - startTime) >= 150)     // 0.2��
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
	glBegin(GL_POLYGON);
	if (x == 2) // ä��
	{
		glTexCoord2d(92 / 433.0, 186 / 742.0);     glVertex3d(-0.5, -0.33, 0.0);      // ���� �Ʒ�    
		glTexCoord2d(92 / 433.0, 153 / 742.0);     glVertex3d(-0.5, 0.33, 0.0);       // ���� ��
		glTexCoord2d(142 / 433.0, 153 / 742.0);     glVertex3d(0.5, 0.33, 0.0);        // ������ ��
		glTexCoord2d(142 / 433.0, 186 / 742.0);     glVertex3d(0.5, -0.33, 0.0);       // ������ �Ʒ�
	}
	else
	{
		glTexCoord2d((1 + 40 * x) / 433.0, 186 / 742.0);     glVertex3d(-0.75, -0.33, 0.0);       // ���� �Ʒ�    
		glTexCoord2d((1 + 40 * x) / 433.0, 153 / 742.0);     glVertex3d(-0.75, 0.33, 0.0);        // ���� ��
		glTexCoord2d((33 + 40 * x) / 433.0, 153 / 742.0);     glVertex3d(-0.15, 0.33, 0.0);         // ������ ��
		glTexCoord2d((33 + 40 * x) / 433.0, 186 / 742.0);     glVertex3d(-0.15, -0.33, 0.0);        // ������ �Ʒ�
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
		JumpPower -= 0.5f;		// �� �����Ӹ��� ���������� ���ش�. 
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