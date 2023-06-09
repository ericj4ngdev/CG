#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Vector2D mPos;
	Vector2D mVelo;
	Vector2D mSize;
	GLuint m_Texid;			// 텍스트 식별자 아이디 생성
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
	void virtual init() {};				// 초기화
	void virtual Render() {};			// 그리기
	void virtual Transform() {};		// 실시간 위치 정보
	bool virtual Collide(Sprite other) { return false; };
	void SetmPos(float x, float y) { mPos = Vector2D(x, y); };
	void loadTexture();			// 텍스쳐 로드
	void Release();				// sprite관련 자원 해제
	void DrawBox(float size);	// 박스 그리기(3차원)
};

#endif