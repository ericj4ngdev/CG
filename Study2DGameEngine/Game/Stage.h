#ifndef STAGE_H_
#define STAGE_H_

class Stage
{
private:
	Sprite m_Sprite;
public:
	Stage();
	~Stage();

	// 위에 세 개는 Sprite에 있는 함수 그대로 가져옴
	void init();
	void Release();
	void Render();
	void FrameMove();		// 움직임 추가
};

#endif