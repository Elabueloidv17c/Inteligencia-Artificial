#pragma once
#include "Headers.h"
#include "Vector2.h"
#include "Math.h"

class Boid
{
	Vector2u			m_textureCenter;
	Texture				m_texture;
	Sprite				m_sprite;

	float				m_acceleration;
	float				m_currentSpeed;
	float				m_timer;
	float				m_waitTime;
	float				m_speed;
	float				m_mass;

	Vector2				m_direction;
	Vector2				m_position;
	Vector2				m_steeringForce;
	Vector2				m_steeringDirection;

	float				m_seekMagnitude;
	float				m_fleeMagnitude;
	float				m_arriveMagnitude;
	float				m_pursueMagnitude;
	float				m_evadeMagnitude;
	float				m_wanderMagnitude;
	float				m_wanderTMagnitude;
	float				m_wanderRMagnitude;

	Boid*				m_seekObjective;
	Boid*				m_fleeObjective;
	Boid*				m_evadeObjective;
	Boid*				m_pursueObjective;
	Boid*				m_arriveObjective;

public:

	Boid();
	~Boid();

	void DrawLine(Vector2 position, Vector2 direction, RenderWindow& window, float magnitude);

	bool Initialize(AgentData& agent);
	void Render(RenderWindow& window);
	void Update(float deltaTime);

	void SetSeekObjective(Boid* objective);
	void SetFleeObjective(Boid* objective);
	void SetArriveObjective(Boid* objective);
	void SetPursueObjective(Boid* objective);
	void SetEvadeObjective(Boid* objective);
	void SetPosition(int x, int y);

	Boid* Get();

	static Vector2 Seek(const Vector2& position, const Vector2& objective, float magnitude);
	static Vector2 Flee(const Vector2& position, const Vector2& danger, const float& magnitude, const float& radius);
	static Vector2 Arrive(const Vector2& position, const Vector2& objective, float radius, float magnitude);
	
	static Vector2 Pursue(const Vector2& position, const Boid* objective, float magnitude, float projectedTime, float deltaTime);
	static Vector2 Evade(const Vector2& position, const Boid* danger, float magnitude, float radius, float projectedTime, float deltaTime);

	static Vector2 Wander(const Vector2& position, const Vector2& direction, int min, int max, float magnitude, float deltaTime, float& currentTime, float timeLimit);
	static Vector2 Wander(const Vector2& position, int min, int max, float magnitude);

	static Vector2 Wander(const Vector2& position, const Vector2& direction, float magnitude, float distProj, float radius, int angle, 
	float deltaTime, float& currentTime, float timeLimit);

};

