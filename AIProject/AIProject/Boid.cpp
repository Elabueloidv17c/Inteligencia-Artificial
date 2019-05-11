#include "Boid.h"

Boid::Boid()
{

}

Boid::~Boid()
{

}

void Boid::Initialize()
{

}

void Boid::Destroy()
{

}

void Boid::Update()
{

}

void Boid::Render()
{

}

//Behaviours
Vector2 Boid::Seek(Vector2 position, Vector2 objective, float magnitude)
{
	Vector2 distance = objective - position;
	
	distance.Normalize();
	return distance * magnitude;
}

Vector2 Boid::Flee(Vector2 position, float magnitude, Vector2 danger, float radius)
{
	Vector2 distance = position - danger;

	if (distance.Magnitude() <= radius)
	{
		distance.Normalize();
		return distance * magnitude;
	}

	return Vector2();
}

Vector2 Boid::Arrive(Vector2 position, Vector2 objective, float radius, float magnitude)
{
	Vector2 distance = objective - position;

	Vector2 force = distance;
	force.Normalize();
	force *= magnitude;

	if (force.Magnitude() <= radius)
	{
		return force *= distance.Magnitude() / radius;
	}

	return force;
}

Vector2 Boid::Pursue(Vector2 position, float magnitude, Vector2 objective, float time, float velocity)
{
	Vector2 direction = objective - position;
	float distance = direction.Magnitude();
	direction.Normalize();

	Vector2 projectedPosition = objective + (direction * time * velocity);

	if (distance <= projectedPosition.Magnitude())
	{
		projectedPosition = objective + (direction * distance);
	}

	return Seek(position, projectedPosition, magnitude);
}

Vector2 Boid::Evade(Vector2 position, float magnitude, Vector2 danger, float radius, float time, float velocity)
{
	Vector2 direction = position - danger;
	float distance = direction.Magnitude();
	direction.Normalize();

	Vector2 projectedDanger = danger + (direction * time * velocity * HALF);

	if (distance <= radius)
	{
		Flee(position, magnitude, projectedDanger, radius);
	}

	return Vector2();
}

Vector2 Boid::ObstacleAvoidance()
{
	return Vector2();
}

Vector2 Boid::Wander()
{
	return Vector2();
}