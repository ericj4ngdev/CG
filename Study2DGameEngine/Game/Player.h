#ifndef PLAYER_H_
#define PLAYER_H_
class Player : public Sprite
{
public:
	Vector2D	mVelo;
	float MoveSpeed;
	float gravity;
	float JumpPower;	
	bool OnCollide;
	bool isAttack;

public:
	void initPos() override;
	void initTexture(const char *name) override;
	void Transform() override;
	void Render() override;
	bool Collide(Sprite other) override;
	void Move();
	void Attack();

	// void IsGround(Sprite& other);
};

#endif