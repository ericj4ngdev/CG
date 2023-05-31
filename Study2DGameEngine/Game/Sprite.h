#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Vector2D mPos;
	Vector2D mSize;
	GLuint m_Texid;			// �ؽ�Ʈ �ĺ��� ���̵� ���� 
	//Texture	m_Tex;			// �ؽ��� ���̴� �κ� 
	Color4f mColor;

public : 
	void virtual init() {};				// �ʱ�ȭ
	void virtual Render() {};				// �׸���

	void loadTexture();			// �ؽ��� �ε�
	void Release();				// sprite���� �ڿ� ����
	void DrawBox(float size);	// �ڽ� �׸���(3����)
	bool Collide(Sprite& other);
};

#endif