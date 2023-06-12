#ifndef PLAYER_H_
#define PLAYER_H_
class Player : public cObject
{
private:
	Vector2D mVelo;
	float MoveSpeed;
	float gravity;
	float JumpPower;
	bool OnGround;
	bool OnCollide;
	bool isAttack;
public:
	// �ʱ�ȭ�� ������
	// Player() {};
	// �� ������ init���� 
	void init();		// ������Ʈ�� �ʱ�ȭ?
	void Transform();
	void Render();
	bool Collide(Enemy other);
	void Move();
	// void Attack();
};

#endif