#ifndef VECTOR2F_H_
#define VECTOR2F_H_
#include<math.h>

class Vector2D
{
	float x;
	float y;
public:
	Vector2D();
	~Vector2D();
	Vector2D(float tx, float ty) : x(tx), y(ty) {}
	float getx() const {}
	float gety() const {}
	Vector2D operator+ (const Vector2D& v) const;
	Vector2D operator- (const Vector2D& v) const;
	Vector2D operator* (const Vector2D& v) const;
	Vector2D operator/ (const Vector2D& v) const;
	bool operator ==(const Vector2D& v) const;
};

#endif