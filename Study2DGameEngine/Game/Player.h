#ifndef PLAYER_H_
#define PLAYER_H_
class Player : public Sprite
{
private:
	float MoveSpeed = 2.0f;
	float Top, Bottom, Left, Right;
	float gravity;
	float JumpPower;
	bool OnGround;
public:
	void init() override;
	void Render() override;
	bool Collide(Sprite& other) override;
	void Move();
	void IsGround(Sprite& other);
};

#endif