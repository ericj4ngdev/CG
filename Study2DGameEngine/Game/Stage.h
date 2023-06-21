#ifndef STAGE_H_
#define STAGE_H_

class Stage
{
private:
	BackGround BackGround;
	Player mPlayer;
	Enemy mZombie;
	Enemy mLeopard;
	Ground arrground[96];
	Ground arrPlatform1[3];
	Ground arrPlatform2[10];
	Ground arrPlatform3[6];
	Ground arrPlatform4[9];
	Ground test;

public:
	Stage();
	virtual ~Stage();
	int groundSpeed;

	void init();
	void Release();
	void Render();
	void Transform();
	void FrameMove();		// 움직임 추가
	void Collide();	
};

#endif