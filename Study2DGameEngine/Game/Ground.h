#ifndef GROUND_H_
#define GROUND_H_
class Ground : public cObject
{
	bool OnCollide;

public:
	void init();
	void Transform();
	void Render();
};

#endif
