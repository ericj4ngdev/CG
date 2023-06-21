#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Vector2D	mPos;	
	Vector2D	mSize;
	GLuint		m_Texid;			// �ؽ�Ʈ �ĺ��� ���̵� ����
	Texture		m_Tex;
	Color4f		mColor;
	float		mTop;
	float		mBottom;
	float		mLeft;
	float		mRight;
	Vector2D	vLT;
	Vector2D	vRT;
	Vector2D	vRB;
	Vector2D	vLB;	
	bool		OnGround;

public : 
	// Sprite(){};
	// virtual ~Sprite() {};
	void virtual initPos() {};						// ��ġ �ʱ�ȭ
	void virtual initTexture(const char *name) {};		// �ʱ�ȭ
	void virtual Transform() {};		// �ǽð� ��ġ ����
	void virtual Render() {};			// �׸���
	bool virtual Collide(Sprite other) { return false; };
public:
	void SetmPos(float x, float y) { mPos = Vector2D(x, y); };
	void loadTexture();			// �ؽ��� �ε�
	void Release();				// sprite���� �ڿ� ����
	void DrawBox(float size);	// �ڽ� �׸���(3����)
};

#endif