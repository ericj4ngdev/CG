#ifndef STAGE_H_
#define STAGE_H_

class Stage
{
private:
	int n;
public:
	Stage();
	~Stage();

	void init();
	void Release();
	void Render();
	void FrameMove();
};

#endif