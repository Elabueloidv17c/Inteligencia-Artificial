#pragma once
#include "Headers.h"

class Vector2
{
public:

	//Members
	float x, y;

	//Constructors
	Vector2(float x, float y);
	Vector2();

	~Vector2();

	//Methods

	void Normalize();

	float Cross(const Vector2& other);
	float Dot(const Vector2& other);
	
	float SqrtMagnitude();
	float Magnitude();

	//Operators
	Vector2 operator + (const float& add) const;
	Vector2 operator + (const Vector2& other) const;

	Vector2& operator += (const float& add);
	Vector2& operator += (const Vector2& other);

	Vector2 operator - (const float& sub) const;
	Vector2 operator - (const Vector2& other) const;

	Vector2& operator -= (const float& sub);
	Vector2& operator -= (const Vector2& other);

	Vector2& operator *= (const Vector2& other);
	Vector2& operator *= (const float& mul);

	Vector2 operator * (const Vector2& other);
	Vector2 operator * (const float& mul) const;
	
	Vector2 operator / (const Vector2& other);
	Vector2 operator / (const float& div) const;

	Vector2& operator /= (const Vector2& other);
	Vector2& operator /= (const float& div);

	Vector2 operator - () const;

	bool operator == (const Vector2& other) const;
	bool operator != (const Vector2& other) const;
};