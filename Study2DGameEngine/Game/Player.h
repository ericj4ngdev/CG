#ifndef PLAYER_H_
#define PLAYER_H_
class Player : public Sprite
{
private:
	float MoveSpeed;
	float gravity;
	float JumpPower;	
	bool OnCollide;
	bool isAttack;

public:
	void init() override;
	void init(char* name);
	void Transform() override;
	void Render() override;
	bool Collide(Sprite other) override;
	void Move();
	void Attack();

	// void IsGround(Sprite& other);
};

#endif