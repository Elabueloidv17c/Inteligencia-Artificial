#pragma once
#include "Obstacle.h"
class CircleObstacle : public Obstacle
{
#ifdef DEBUG
	CircleShape
		m_shape;
#endif // DEBUG

	float m_radius;

public:

#ifdef DEBUG
	CircleShape*
		GetShape();

	void
		SetShape(CircleShape shape), SetColor(Color color);
#endif // DEBUG

	const float* GetRadius();

	CircleObstacle(Vector2 position, float radius, Color color);
	CircleObstacle() = default;
	~CircleObstacle();
};

