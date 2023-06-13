#include "Include.h"

void Ground::init()
{
	mTransform.mPos = Vector2D(0, 0);		// �ʱ���ġ
	mTransform.mSize = Vector2D(50, 100);
	mSprite.m_Texid = NULL;
	mSprite.mColor = Color4f(1, 1, 1, 1);

	OnCollide = false;
	mSprite.loadTexture();
}

void Ground::Transform()
{
	mSprite.SquareArea(mTransform.mPos, mTransform.mSize);
	
}

void Ground::Render()
{
	mSprite.RenderSquare(mTransform.mPos, mTransform.mSize);
	// glPushMatrix();			// ���� �𵨺� ����� ���ÿ� �����ϴ� �Լ�
	// glBindTexture(GL_TEXTURE_2D, m_Texid);		// ���� Ȱ��ȭ�� �ؽ�ó ���ֿ� 2D �ؽ�ó�� ���ε��ϴ� �Լ�
	// 
	// glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);		// ������ ������ �����ϴ� �Լ�
	// 
	// glMatrixMode(GL_MODELVIEW);			// ������ ��� ��带 �����ϴ� �Լ�
	// glLoadIdentity();					// ���� ����� ���� ��ķ� �ʱ�ȭ
	// 
	// glTranslatef(mPos.x, g_Extern.WINDOWSIZE_HEIGHT - mPos.y, 0);	  // â �ϴ�
	// glScalef(mSize.x, mSize.y, 1);	// â �ϴ� �� ä���
	// 
	// DrawBox(1);
	// 
	// glBindTexture(GL_TEXTURE_2D, 0);		// �ؽ�ó ����ε�
	// glPopMatrix();			// ���ÿ� ����� ������ �𵨺� ����� �����ϴ� �Լ�
}

bool Ground::Collide(cObject other)
{
	mCollider.CollideArea(mTransform.mPos, mTransform.mSize);
	return mCollider.Collide(other);
}

void Ground::Release() 
{
	mSprite.Release();
}

void Ground::SetmPos(float x, float y) 
{
	mTransform.mPos = Vector2D(x, y);
}