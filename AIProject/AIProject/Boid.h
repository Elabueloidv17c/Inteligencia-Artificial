#pragma once
#include "Headers.h"
#include "Vector2.h"

class Boid
{
	Vector2			m_position;
	Vector2			m_direction;
	float			m_force;
	float			m_speed;

public:

	Boid();
	~Boid();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	static Vector2 ObstacleAvoidance();
	static Vector2 Wander();
	static Vector2 Seek(Vector2 position, Vector2 objective, float magnitude);
	static Vector2 Flee(Vector2 position, float magnitude, Vector2 danger, float radius);
	static Vector2 Arrive(Vector2 position, Vector2 objective, float radius, float magnitude);
	static Vector2 Pursue(Vector2 position, float magnitude, Vector2 objective, float time, float velocity);
	static Vector2 Evade(Vector2 position, float magnitude, Vector2 danger, float radius, float time, float velocity);
};

