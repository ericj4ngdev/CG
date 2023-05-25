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
	void init(){}				// 초기화
	void Release() {}			// sprite관련 자원 해제
	void DrawBox(){}			// 박스 그리기(3차원)
	void Render(){}				// 그리기
};

#endif