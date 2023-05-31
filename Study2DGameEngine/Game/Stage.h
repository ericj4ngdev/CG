#ifndef STAGE_H_
#define STAGE_H_

class Stage
{
private:
	Player mPlayer;
	Ground mGround;

public:
	Stage();
	virtual ~Stage();

	void init();
	void Release();
	void Render();
	void FrameMove();		// ������ �߰�
	void Collide();
	
};

#endif