#ifndef COLLIDER_H_
#define COLLIDER_H_

class cObject;

class Collider 
{
	Transform	mTransform;
	float		Top;
	float		Bottom;
	float		Left;
	float		Right;
	Vector2D	vLT;
	Vector2D	vRT;
	Vector2D	vRB;
	Vector2D	vLB;
	bool		OnCollide;
public:
	void CollideArea(Vector2D pos, Vector2D size);
	bool Collide(cObject other);
	bool CollidebyVector(cObject& other);
	void cal(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, Vector2D& cross);
	float ccw(Vector2D a, Vector2D b);
	float ccw(Vector2D p, Vector2D a, Vector2D b);
};
#endif