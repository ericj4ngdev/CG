#ifndef GROUND_H_
#define GROUND_H_
class Ground : public Sprite
{
public:
	void init() override;
	void Transform() override;
	void Render() override;
	void Render(int num);
};

#endif
