#ifndef ENEMY_H_
#define ENEMY_H_
class Enemy : public Sprite
{
public:
	Vector2D	mVelo;
	float MoveSpeed;
	float gravity;
	// bool OnGround;
	bool OnCollide;
public:
	void initPos() override;
	void initTexture(const char *name) override;
	void Transform() override;
	void Render() override;
	bool Collide(Sprite other) override;
	void InputController();

};

#endif