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
	void init();			// �ʱ�ȭ
	void Release();			// sprite���� �ڿ� ����
	void DrawBox(float size);	// �ڽ� �׸���(3����)
	void Render();			// �׸���
};

#endif