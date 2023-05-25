#pragma once
#include "Vector2D.h"
#include "Color4f.h"
#include <glut.h>

#ifndef SPRITE
#define SPRITE
class Sprite
{
	Vector2D mPos;
	Vector2D mSize;
	GLuint m_Texid;
	Color4f mColor;

public : 
	void init(){}				// �ʱ�ȭ
	void Release() {}			// sprite���� �ڿ� ����
	void DrawBox(){}			// �ڽ� �׸���(3����)
	void Render(){}				// �׸���
};

#endif