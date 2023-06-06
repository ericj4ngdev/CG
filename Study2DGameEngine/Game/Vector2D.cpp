#include "Include.h"

Vector2D::Vector2D(){}
Vector2D::~Vector2D(){}

// float Vector2D::getx() const { return x; }
// float Vector2D::gety() const { return y; }

Vector2D Vector2D::operator+ (const Vector2D& v) const
{
	return Vector2D(x + v.x, y + v.y);
}
Vector2D Vector2D::operator- (const Vector2D& v) const
{
	return Vector2D(x - v.x, y - v.y);
}
Vector2D Vector2D::operator* (float n) const
{
	return Vector2D(x * n, y * n);
}
Vector2D Vector2D::dot (const Vector2D& v) const
{
	return Vector2D(x * v.x, y * v.y);
}

double Vector2D::cross(const Vector2D& other) const {
	return x * other.y - y * other.x;
}

Vector2D Vector2D::operator/ (const Vector2D& v) const
{
	return Vector2D(x / v.x, y + v.y);
}
void Vector2D::print() 
{
	std::cout << "(" << x << ", " << y << ")";
}
void Vector2D::operator +=(const Vector2D& v)
{
	*this = Vector2D(x + v.x, y + v.y);
}


bool Vector2D::operator==(const Vector2D& v) const
{
	return x == v.x && y == v.y;
}

Vector2D Vector2D::Normalize()
{
	float k = sqrt(pow(x, 2) + pow(y, 2));
	if (k == 0.0)
		return Vector2D(0.0, 0.0);
	else
	{
		x = x / k;
		y = y / k;
		return Vector2D(x, y);
	}
}

float Vector2D::Length()
{
	float w = sqrt(pow((float)x, 2) + pow((float)y, 2));
	return w;
}