#ifndef ENEMY_H_
#define ENEMY_H_
class Enemy : public cObject
{
	
private:
	Vector2D mVelo;
	float gravity;
	bool OnGround;
	bool OnCollide;
public:
	void init();
	void Transform();
	void Render();
	bool Collide(Player other);
	void Move();

};

#endif