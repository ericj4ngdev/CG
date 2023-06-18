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
	bool isIdle;
	bool isWalk;
	bool isAttack;
	bool isDown;
	bool isinc;
	int count;
	enum State
	{
		IDLE,
		WALK,
		ATTACK,
	};
	State currentState;

public:
	Player() : currentState(IDLE){}
	void initPos() override;
	void initTexture(const char *name) override;
	void Transform() override;
	void Render() override;
	bool Collide(Sprite other) override;
	void Idle();
	void Walk(int x);
	void Attack(int x);
	void InputWalkKey();
	void InputAttackKey();
	void Controller();
	void Move();
	void Attack();

	// void IsGround(Sprite& other);
};

#endif