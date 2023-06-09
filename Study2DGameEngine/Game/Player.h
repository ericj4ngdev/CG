#ifndef PLAYER_H_
#define PLAYER_H_
class Player : public Sprite
{
private:
	float MoveSpeed;
	float gravity;
	float JumpPower;
	bool OnGround;
	bool OnCollide;
	bool isAttack;
public:
	void init() override;
	void Transform() override;
	void Render() override;
	bool Collide(Sprite other) override;
	// void cal(Sprite& other, Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4);
	void Update(int value);
	void Move();
	void Attack();

	void IsGround(Sprite& other);
};

#endif