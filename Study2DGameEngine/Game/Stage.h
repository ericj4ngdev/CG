#ifndef STAGE_H_
#define STAGE_H_

class Stage
{
private:
	Player mPlayer;
	Ground mGround1;
	Ground mGround2;
	Ground mGround3;
	Ground mGround4;
	Ground mGround5;
	Ground mPlatform1;
	Ground mPlatform2;
	Ground mPlatform3;
	Ground mPlatform4;
	// std::vector<Ground> arrground;

public:
	Stage();
	virtual ~Stage();

	void init();
	void Release();
	void Render();
	void Transform();
	void FrameMove();		// 움직임 추가
	void Collide();
	
};

#endif