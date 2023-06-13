#ifndef GROUND_H_
#define GROUND_H_
class Ground : public cObject
{
public:
	bool OnCollide;
public:
	void init();
	void Transform();
	void Render();
	bool Collide(cObject other);
	void SetmPos(float x, float y);
	void Release();
};

#endif
