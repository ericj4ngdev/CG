#ifndef STAGE_H_
#define STAGE_H_

class Stage
{
private:
	Sprite mPlayer;
	Sprite mGround;
public:
	Stage();
	virtual ~Stage();

	void init();
	void Release();
	void Render();
	void FrameMove();		// 움직임 추가
	void Collide();
	
};

#endif