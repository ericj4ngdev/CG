#ifndef VECTOR2D_H_
#define VECTOR2D_H_

class Vector2D
{
public:
	float x;
	float y;
	Vector2D();
	~Vector2D();
	Vector2D(float tx, float ty) : x(tx), y(ty) {}
	//float getx() const {}
	//float gety() const {}
	Vector2D operator+ (const Vector2D& v) const;
	Vector2D operator- (const Vector2D& v) const;
	Vector2D operator* (const Vector2D& v) const;
	Vector2D operator/ (const Vector2D& v) const;
	bool operator ==(const Vector2D& v) const;
};

#endif