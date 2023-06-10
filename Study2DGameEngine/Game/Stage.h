#ifndef STAGE_H_
#define STAGE_H_

class Stage
{
private:
	Player mPlayer;
	Enemy mEnemy;
	Ground arrground[14];
	Ground arrPlatform1[8];
	Ground arrPlatform2[10];

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