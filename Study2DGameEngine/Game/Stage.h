#ifndef STAGE_H_
#define STAGE_H_

class Stage
{
private:
	Sprite m_Sprite;
public:
	Stage();
	~Stage();

	// ���� �� ���� Sprite�� �ִ� �Լ� �״�� ������
	void init();
	void Release();
	void Render();
	void FrameMove();		// ������ �߰�
};

#endif