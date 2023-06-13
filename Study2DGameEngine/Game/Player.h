#ifndef PLAYER_H_
#define PLAYER_H_
class Player : public cObject
{
public:
	Vector2D mVelo;
	float MoveSpeed;
	float gravity;
	float JumpPower;
	bool OnGround;
	bool OnCollide;
	bool isAttack;
public:
	// 초기화는 생성자
	// Player() {};
	// 값 대입은 init에서 
	void init();		// 컴포넌트들 초기화?
	void Transform();
	void Render();
	bool Collide(cObject other);
	void Release();
	void Move();
	// void Attack();
};

#endif