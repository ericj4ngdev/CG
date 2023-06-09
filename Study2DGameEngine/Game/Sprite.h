#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Vector2D mPos;
	Vector2D mVelo;
	Vector2D mSize;
	GLuint m_Texid;			// �ؽ�Ʈ �ĺ��� ���̵� ����
	Color4f mColor;
	float Top;
	float Bottom;
	float Left;
	float Right;
	Vector2D vLT;
	Vector2D vRT;
	Vector2D vRB;
	Vector2D vLB;	

public : 
	// Sprite(float x, float y) : mPos(x, y) {}
	void virtual init() {};				// �ʱ�ȭ
	void virtual Render() {};			// �׸���
	void virtual Transform() {};		// �ǽð� ��ġ ����
	bool virtual Collide(Sprite other) { return false; };
	void SetmPos(float x, float y) { mPos = Vector2D(x, y); };
	void loadTexture();			// �ؽ��� �ε�
	void Release();				// sprite���� �ڿ� ����
	void DrawBox(float size);	// �ڽ� �׸���(3����)
};

#endif