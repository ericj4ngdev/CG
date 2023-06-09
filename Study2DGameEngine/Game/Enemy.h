#ifndef ENEMY_H_
#define ENEMY_H_
class Enemy : public Sprite
{
private:
	float MoveSpeed;
	float gravity;
	bool OnGround;
	bool OnCollide;
public:
	void init() override;
	void Transform() override;
	void Render() override;
	bool Collide(Sprite other) override;
	void Move();
	void IsGround(Sprite& other);

};

#endif