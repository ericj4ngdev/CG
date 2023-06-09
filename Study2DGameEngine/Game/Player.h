#ifndef PLAYER_H_
#define PLAYER_H_	
enum State
{
	IDLE,
	WALK,
	ATTACK,
	JUMP,
	SIT,
};

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
	bool isJump;
	bool isSit;
	bool isDown;
	bool isKeyDown;
	bool isAttackKeyDown;
	bool isinc;
	int attackRange;
	DWORD startTime;
	int count;
	int direction;

	State currentState;

public:
	Player() : currentState(IDLE){}
	void initPos() override;
	void initTexture(const char *name) override;
	void Transform() override;
	void Render() override;
	bool Collide(Sprite other) override;

public:
	void Idle();
	void Walk(int x);
	void Attack();
	void Jump();
	void Sit();
public:
	void InputWalkKey();
	void InputSitKey();
	void StateMachine();
public:
	void InputController();
	void DrawCollide();
	void DrawCollide(Sprite& other);
	// void IsGround(Sprite& other);
};

#endif