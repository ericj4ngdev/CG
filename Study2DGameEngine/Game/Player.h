#ifndef PLAYER_H_
#define PLAYER_H_
class Player : public Sprite
{
private:
	float MoveSpeed = 2.0f;

public:
	void init() override;
	void Render() override;
	void Move();
};

#endif