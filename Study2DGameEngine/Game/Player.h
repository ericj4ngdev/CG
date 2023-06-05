#ifndef PLAYER_H_
#define PLAYER_H_
class Player : public Sprite
{
private:
	float MoveSpeed;
	float gravity;
	float JumpPower;
	bool OnGround;
public:
	void init() override;
	void Transform() override;
	void Render() override;
	bool Collide(Sprite& other) override;
	bool CollidebyVector(Sprite& other);
	void Move();

	void IsGround(Sprite& other);
};

#endif