#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::~Vector2()
{

}

void Vector2::Normalize()
{
	x = x / Magnitude();
	y = y / Magnitude();
}

float Vector2::SqrtMagnitude()
{
	return (x * x) + (y * y);
}

float Vector2::Magnitude()
{
	float v = sqrt(SqrtMagnitude());
	return v;
}

float Vector2::Dot(const Vector2& other)
{
	return (x * other.x) + (y * other.y);
}

float Vector2::Cross(const Vector2& other)
{
	return (x * other.y) - (y * other.x);
}

Vector2& Vector2:: operator += (const Vector2& other)
{
	x += other.x; 
	y += other.y; 
	
	return *this;
}

Vector2& Vector2::operator += (const float& add)
{
	x += add;
	y += add;

	return *this;
}

Vector2 Vector2::operator + (const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator + (const float& add) const
{
	return Vector2(x + add, y + add);
}

Vector2& Vector2::operator -= (const Vector2& other)
{
	x -= other.x; 
	y -= other.y; 
	
	return *this;
}

Vector2& Vector2::operator -= (const float& sub)
{
	x -= sub;
	y -= sub;

	return *this;
}

Vector2 Vector2::operator - (const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator - (const float& sub) const
{
	return Vector2(x - sub, y - sub);
}

Vector2& Vector2::operator *= (const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2 Vector2::operator * (const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2& Vector2::operator *= (const float& mul)
{
	x *= mul;
	y *= mul;

	return *this;
}

Vector2 Vector2::operator * (const float& mul) const
{
	return Vector2(x * mul, y * mul);
}

Vector2& Vector2::operator /= (const Vector2& other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

Vector2 Vector2::operator / (const Vector2& other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

Vector2& Vector2::operator /= (const float& div)
{
	x /= div;
	y /= div;

	return *this;
}

Vector2 Vector2::operator / (const float& div) const
{
	return Vector2(x / div, y / div);
}

Vector2 Vector2::operator - () const
{
	return Vector2(-x, -y);
}

bool Vector2::operator == (const Vector2 & other) const
{
	if (x == other.x && y == other.y)
	{
		return true;
	}

	return false;
}

bool Vector2::operator != (const Vector2 & other) const
{
	if (x != other.x || y != other.y)
	{
		return true;
	}

	return false;
}
