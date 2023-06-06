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
	void print();
	Vector2D operator+ (const Vector2D& v) const;
	Vector2D operator- (const Vector2D& v) const;
	Vector2D operator* (float n) const;
	Vector2D dot (const Vector2D& v) const;
	double cross(const Vector2D& other) const;
	Vector2D operator/ (const Vector2D& v) const;

	void operator +=(const Vector2D& v);

	bool operator ==(const Vector2D& v) const;
	Vector2D Normalize();
	float Length();
};

#endif