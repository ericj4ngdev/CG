#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Vector2D mPos;
	Vector2D mSize;
	GLuint m_Texid;			// 텍스트 식별자 아이디 생성 
	//Texture	m_Tex;			// 텍스쳐 쓰이는 부분 
	Color4f mColor;

public : 
	void virtual init() {};				// 초기화
	void virtual Render() {};				// 그리기

	void loadTexture();			// 텍스쳐 로드
	void Release();				// sprite관련 자원 해제
	void DrawBox(float size);	// 박스 그리기(3차원)
	bool Collide(Sprite& other);
};

#endif