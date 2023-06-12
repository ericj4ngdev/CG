#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Vector2D	mVelo;
	GLuint		m_Texid;			// �ؽ�Ʈ �ĺ��� ���̵� ����
	Color4f		mColor;
	float		Top;
	float		Bottom;
	float		Left;
	float		Right;
	Vector2D	vLT;
	Vector2D	vRT;
	Vector2D	vRB;
	Vector2D	vLB;

public : 
	// Sprite(){};
	// virtual ~Sprite() {};
	// �׸���
	void SquareArea(Vector2D pos, Vector2D size);
	void RenderSquare(Vector2D pos, Vector2D size);
	void loadTexture();			// �ؽ��� �ε�
	void Release();				// sprite���� �ڿ� ����
	void DrawBox(float size);	// �ڽ� �׸���(3����)
};

#endif