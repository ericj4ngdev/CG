#ifndef GROUND_H_
#define GROUND_H_
class Ground : public Sprite
{
	bool OnCollide;

public:
	
	void init() override;
	void Transform() override;
	void Render() override;
	bool Collide(Sprite other);
	bool CollidebyVector(Sprite& other);
	void cal(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, Vector2D& cross);
	float ccw(Vector2D a, Vector2D b);
	float ccw(Vector2D p, Vector2D a, Vector2D b);
};

#endif
