#include "Include.h"

void Ground::init()
{
	mPos = Vector2D(300, 100);
	mSize = Vector2D(100, 100);
	m_Texid = NULL;
	mColor = Color4f(0, 0, 0, 1);

	loadTexture();
}

void Ground::Transform()
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
void Ground::Render(int num) 
{
	
}
void Ground::Render()
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