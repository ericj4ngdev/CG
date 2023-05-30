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
	void init();				// �ʱ�ȭ
	void init(int yt);
	void loadTexture();			// �ؽ��� �ε�
	void Release();				// sprite���� �ڿ� ����
	void DrawBox(float size);	// �ڽ� �׸���(3����)
	void Render(int x);			// �� �׸���
	void Render();				// �׸���
	bool Collide(Sprite& other);
	// void SetPosition(float x, float y, float z);
};

#endif