#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Vector2D mPos;
	Vector2D mSize;
	GLuint m_Texid;
	Texture	m_Tex;
	Color4f mColor;

public : 
	void init();			// 초기화
	void Release();			// sprite관련 자원 해제
	void DrawBox(float size);	// 박스 그리기(3차원)
	void Render();			// 그리기
};

#endif