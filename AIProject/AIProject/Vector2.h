#pragma once
#include <SFML/Graphics.hpp>

class Vector2
{
public:

	//Members
	float 
	x, y;

	//Constructors
	Vector2(sf::Vector2f slfmVector);
	Vector2(float x, float y);
	Vector2();

	~Vector2();

	//Methods
	void 
	Truncated(float maxMagnitude), Normalize();

	Vector2 
	Projection(Vector2 other), Normalized();

	float 
	Cross(const Vector2& other), Dot(const Vector2& other),
	SqrtMagnitude(), Magnitude();

	//Operators
	Vector2 operator + (const float& add) const;
	Vector2 operator + (const Vector2& other) const;

	Vector2 operator - (const float& sub) const;
	Vector2 operator - (const Vector2& other) const;
	Vector2 operator - () const;

	Vector2 operator * (const Vector2& other);
	Vector2 operator * (const float& mul) const;
	
	Vector2 operator / (const Vector2& other);
	Vector2 operator / (const float& div) const;

	Vector2& operator += (const float& add);
	Vector2& operator += (const Vector2& other);

	Vector2& operator -= (const float& sub);
	Vector2& operator -= (const Vector2& other);

	Vector2& operator *= (const Vector2& other);
	Vector2& operator *= (const float& mul);

	Vector2& operator /= (const Vector2& other);
	Vector2& operator /= (const float& div);


	bool operator == (const Vector2& other) const;
	bool operator == (const float& other) const;

	bool operator != (const Vector2& other) const;
	bool operator != (const float& other) const;
};