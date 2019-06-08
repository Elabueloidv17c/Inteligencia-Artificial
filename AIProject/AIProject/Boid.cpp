#include "Boid.h"
#include "Timer.h"

Boid::Boid()
{
	m_timer = 0.0f;
	m_seekObjective = nullptr;
	m_fleeObjective = nullptr;
	m_evadeObjective = nullptr;
	m_pursueObjective = nullptr;
	m_arriveObjective = nullptr;
}

Boid::~Boid()
{

}

void Boid::DrawLine(Vector2 position, Vector2 direction, RenderWindow& window, float magnitude)
{
	direction *= magnitude;

	Vertex line[2] = { 
	Vertex(Vector2f(position.x , position.y)), 
	Vertex(Vector2f(position.x + direction.x, position.y + direction.y)) };

	window.draw(line, 2, sf::Lines);
}

bool Boid::Initialize(AgentData& agent)
{
	m_position = agent.position;
	m_direction = agent.direction;

	m_acceleration = agent.acceleration;
	m_waitTime = agent.waitTime;
	m_currentSpeed = 0.0f;
	m_speed = agent.speed;
	m_mass = agent.mass;

	m_seekMagnitude = agent.seekMagnitude;
	m_fleeMagnitude = agent.fleeMagnitude;
	m_arriveMagnitude = agent.arriveMagnitude;
	m_pursueMagnitude = agent.pursueMagnitude;
	m_evadeMagnitude = agent.evadeMagnitude;
	m_wanderMagnitude = agent.wanderMagnitude;
	m_wanderTMagnitude = agent.wanderTMagnitude;
	m_wanderRMagnitude = agent.wanderRMagnitude;

	if (!m_texture.loadFromFile(agent.texturePath))
	{
		return false;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position.x, m_position.y);

	return true;
}

void Boid::Update(float deltaTime)
{	
	//Set steering force to 0 at the beginning of each frame
	m_steeringForce = Vector2();

	//Setting up the current speed
	m_currentSpeed += m_acceleration * deltaTime;

	//If current speed is bigger than max speed
	if (m_currentSpeed > m_speed)
	{
		//truncate current speed to max speed
		m_currentSpeed = m_speed;
	}

	//------------------------------------------------------------------------------------------------------------------
	//ADDING FORCES
	//------------------------------------------------------------------------------------------------------------------
	if (m_seekObjective != nullptr)
	{
		m_steeringForce += Seek(m_position, m_seekObjective->m_position, m_seekMagnitude);
	}
	if (m_fleeObjective != nullptr)
	{
		m_steeringForce += Flee(m_position, m_fleeObjective->m_position, m_fleeMagnitude, 200);
	}
	if (m_arriveObjective != nullptr)
	{
		m_steeringForce += Arrive(m_position, m_arriveObjective->m_position, 100, m_arriveMagnitude);
	}
	if (m_pursueObjective != nullptr)
	{
		m_steeringForce += Pursue(m_position, m_pursueObjective, m_pursueMagnitude, 4.0f, deltaTime);
	}
	if (m_evadeObjective != nullptr)
	{
		m_steeringForce += Evade(m_position, m_evadeObjective, m_evadeMagnitude, 100, 3.0f, deltaTime);
	}

	m_steeringForce += Wander(m_position, m_direction, m_wanderMagnitude, 300, 150, 120, deltaTime, m_timer, m_waitTime);
	m_steeringForce += Wander(m_position, m_direction, -200, 200, m_wanderTMagnitude, deltaTime, m_timer, m_waitTime);
	m_steeringForce += Wander(m_position, -200, 200, m_wanderRMagnitude);

	//------------------------------------------------------------------------------------------------------------------
	//CALCULATING NEW DIRECTION
	//------------------------------------------------------------------------------------------------------------------

	if (m_steeringForce.Magnitude() > 0)
	{
		m_steeringDirection = (m_steeringForce - m_direction) * m_mass;
		m_direction += m_steeringDirection;
		m_direction.Normalize();

		m_steeringForce.Truncated(m_currentSpeed);
		m_position += m_direction * m_steeringForce.Magnitude() * deltaTime;
	}
}

void Boid::SetSeekObjective(Boid* objective)
{
	m_seekObjective = objective;
}

void Boid::SetFleeObjective(Boid * objective)
{
	m_fleeObjective = objective;
}

void Boid::SetArriveObjective(Boid * objective)
{
	m_arriveObjective = objective;
}

void Boid::SetPursueObjective(Boid * objective)
{
	m_pursueObjective = objective;
}

void Boid::SetEvadeObjective(Boid * objective)
{
	m_evadeObjective = objective;
}

void Boid::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

Boid* Boid::Get()
{
	return this;
}

void Boid::Render(RenderWindow& window)
{
	//Getting the center of the agent's sprite
	m_textureCenter = m_texture.getSize();
	m_textureCenter.x = m_position.x - (m_textureCenter.x * HALF);
	m_textureCenter.y = m_position.y - (m_textureCenter.y * HALF);

	m_sprite.setPosition(m_textureCenter.x, m_textureCenter.y);
	DrawLine(m_position, m_direction, window, m_speed);
	window.draw(m_sprite);
}

//Behaviours
Vector2 Boid::Seek(const Vector2& position, const Vector2& objective, float magnitude)
{
	Vector2 target = objective - position;
	target.Normalize();

	return target *= magnitude;
}

Vector2 Boid::Flee(const Vector2& position, const Vector2& danger, const float& magnitude, const float& radius)
{
	Vector2 target = position - danger;

	if (target.Magnitude() <= radius)
	{
		return -Seek(position, danger, magnitude);
	}

	return Vector2();
}

Vector2 Boid::Arrive(const Vector2& position, const Vector2& objective, float radius, float magnitude)
{
	Vector2 target = objective - position;
	target.Normalize();
	target *= magnitude;

	if ((objective - position).Magnitude() <= radius)
	{
		return target *= (objective - position).Magnitude() / radius;
	}

	return target;
}

Vector2 Boid::Pursue(const Vector2& position, const Boid* objective, float magnitude, float projectedTime, float deltaTime)
{
	Vector2 target = objective->m_position - position;

	Vector2 projectedPosition = objective->m_position + (objective->m_direction * objective->m_currentSpeed * projectedTime);

	if (target.Magnitude() <= projectedPosition.Magnitude())
	{
		projectedPosition = objective->m_position + (objective->m_direction * objective->m_currentSpeed * deltaTime);
	}

	return Seek(position, projectedPosition, magnitude);
}

Vector2 Boid::Evade(const Vector2& position, const Boid* danger, float magnitude, float radius, float projectedTime, float deltaTime)
{
	Vector2 target = position - danger->m_position;

	Vector2 projectedDanger = danger->m_position + (danger->m_direction * danger->m_currentSpeed * projectedTime * HALF);

	if (target.Magnitude() <= radius)
	{
		return Flee(position, projectedDanger, magnitude, radius);
	}

	return Vector2();
}

Vector2 Boid::Wander(const Vector2& position, const Vector2& direction, float magnitude, float distProj, float radius, int angle, 
float deltaTime, float& currentTime, float timeLimit)
{
	currentTime += deltaTime;

	if (currentTime < timeLimit)
	{
		return direction * magnitude;
	}

	currentTime = 0.0f;

	Vector2 ProjectedPosition = position + (direction * distProj);

	float radians = Math::RandomNumber(0, angle) * (PI / 180);
	float finalAngle = (atan(direction.y / direction.x) - ((angle * PI / 180) * HALF)) + radians;

	ProjectedPosition.x += radius * cos(finalAngle);
	ProjectedPosition.y += radius * sin(finalAngle);

	return Seek(position, ProjectedPosition, magnitude);
}

Vector2 Boid::Wander(const Vector2& position, const Vector2& direction, int min, int max, float magnitude, float deltaTime, float& currentTime, float timeLimit)
{
	currentTime += deltaTime;

	if (currentTime < timeLimit)
	{
		return direction * magnitude;
	}

	currentTime = 0.0f;

	return Wander(position, min, max, magnitude);
}

Vector2 Boid::Wander(const Vector2& position, int min, int max, float magnitude)
{
	Vector2 objective = Vector2(Math::RandomNumber(min, max), Math::RandomNumber(min, max));

	return Seek(position, objective, magnitude);
}
