#include "Include.h"

void Sprite::init() 
{
	mPos = Vector2D(0, 0);		// �ʱ���ġ
	mSize = Vector2D(100, 100);
	m_Texid = NULL;
	mColor = Color4f(1, 1, 1, 1);

	loadTexture();
}

void Sprite::init(int yt)
{
	mPos = Vector2D(400, 50);
	mSize = Vector2D(600, 50);
	m_Texid = NULL;
	mColor = Color4f(0, 0, 0, 1);

	loadTexture();
}

void Sprite::loadTexture()
{
	// �ؽ�ó �ε� �� ����
	glGenTextures(1, &m_Texid); // �ؽ�ó �ĺ��� ����
	glBindTexture(GL_TEXTURE_2D, m_Texid); // ������ �ؽ�ó�� ���ε��Ͽ� ����

	// �ؽ�ó �Ű����� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Sprite::Release()
{
	if (m_Texid != NULL)
	{
		glDeleteTextures(1, &m_Texid); // �ؽ�ó �ĺ��� ����
		m_Texid = 0; // �ؽ�ó �ĺ��� �ʱ�ȭ
	}
}

bool Sprite::Collide(Sprite& other)
{
	// �� �˻��ؼ� ��ġ�� 
	if ((mPos.x + mSize.x / 2 >= other.mPos.x - other.mSize.x / 2)
		&& (mPos.x - mSize.x / 2 <= other.mPos.x + other.mSize.x / 2))
	{
		return true;
	}
	return false; // �浹 ���� ����.
}

void Sprite::DrawBox(float size)
{
	// 6�� ���� ��������
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	// 6�� ���� �ε���, �� ���� 4���� �������� ����
	// ������ ���ڷ� ǥ��. 0~7�� v�� ��ǥ�� ����
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	// ������ 8���� ���� ��ǥ�� �����ϴ� 2���� �迭
	GLfloat v[8][3];

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (int i = 0; i < 6; i++)
	{
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);					// ���� ���� ���� ���͸� ����

		glTexCoord2f(0, 1);						// �ؽ�ó ��ǥ ����
		glVertex3fv(&v[faces[i][0]][0]);		// ���� ��ǥ�� ����. ��׸���
		glTexCoord2f(0, 0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1, 0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1, 1);
		glVertex3fv(&v[faces[i][3]][0]);

		glEnd();
	}
}

// player ���� render�Լ� 
void Sprite::Render() 
{
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
		glBindTexture(GL_TEXTURE_2D, m_Texid);		// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

			glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		// ������ ������ �����ϴ� �Լ�

			glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
			glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ

			// ��ǥ�� �߽����� �̵�
			// ���� ��� 
			// glTranslatef((mSize.x / 2) + mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y - (mSize.y / 2), 0);
			// ���߾� ����, ������ ���� ���
			glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);
			glScalef(-mSize.x, mSize.y, 1);
			// if(this->Collide())

			// Collide(other)

			DrawBox(1);

		glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
}

// ground ���� render�Լ� 
void Sprite::Render(int x)
{
	glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	glBindTexture(GL_TEXTURE_2D, m_Texid);		// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�

	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		// ������ ������ �����ϴ� �Լ�

	glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ

	glTranslatef(mPos.x, mPos.y, 0);	  // â �ϴ�
	glScalef(mSize.x, mSize.y, 1);	// â �ϴ� �� ä���

	DrawBox(1);

	glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
}

