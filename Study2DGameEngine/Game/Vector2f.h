#pragma once
class Vector2f
{
	float x;
	float y;
public : 
	Vector2f(float tx, float ty) : x(tx), y(ty) {}
	Vector2f operator+ (const Vector2f& v) const {
		return Vector2f(x + v.x, y + v.y);
	}
	Vector2f operator- (const Vector2f& v) const {
		return Vector2f(x - v.x, y - v.y);
	}
	Vector2f operator* (const Vector2f& v) const {
		return Vector2f(x * v.x, y * v.y);
	}
	Vector2f operator/ (const Vector2f& v) const {
		return Vector2f(x / v.x, y + v.y);
	}

	bool operator ==(const Vector2f& v) const 
	{
		return x == v.x && y == v.y;
	}
};




