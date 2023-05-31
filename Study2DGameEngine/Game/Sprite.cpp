#include "Include.h"

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
