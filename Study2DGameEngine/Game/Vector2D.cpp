#include "Vector2D.h"

Vector2D::Vector2D(){}
Vector2D::~Vector2D(){}

float Vector2D::getx() const { return x; }
float Vector2D::gety() const { return y; }

Vector2D Vector2D::operator+ (const Vector2D& v) const
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator- (const Vector2D& v) const
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator* (const Vector2D& v) const
{
	return Vector2D(x * v.x, y * v.y);
}

Vector2D Vector2D::operator/ (const Vector2D& v) const
{
	return Vector2D(x / v.x, y + v.y);
}

bool Vector2D::operator==(const Vector2D& v) const
{
	return x == v.x && y == v.y;
}
