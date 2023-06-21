#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Vector2D	mPos;	
	Vector2D	mSize;
	GLuint		m_Texid;			// 텍스트 식별자 아이디 생성
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
	void virtual initPos() {};						// 위치 초기화
	void virtual initTexture(const char *name) {};		// 초기화
	void virtual Transform() {};		// 실시간 위치 정보
	void virtual Render() {};			// 그리기
	bool virtual Collide(Sprite other) { return false; };
public:
	void SetmPos(float x, float y) { mPos = Vector2D(x, y); };
	void loadTexture();			// 텍스쳐 로드
	void Release();				// sprite관련 자원 해제
	void DrawBox(float size);	// 박스 그리기(3차원)
};

#endif