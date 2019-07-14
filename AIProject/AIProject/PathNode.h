#pragma once
#include "Headers.h"

class PathNode
{
#ifdef DEBUG
	CircleShape
	m_shape;
#endif // DEBUG

	Vector2 
	m_position;
	
	float 
	m_size, m_roadLimit, m_friction;

public:

	const Vector2* 
	GetPosition();
	
	const float 
	GetSize(), GetRoadLimit(), GetFriction();
	
	const PathNode* 
	Get();

#ifdef DEBUG
	CircleShape*
	GetShape();

	void
	SetShape(CircleShape shape), SetColor(Color color);
#endif // DEBUG


	void
	SetPosition(Vector2 position), SetBounds(float size, float roadLimit, float friction);

	PathNode(Vector2 position, float size, float roadLimit, float friction, Color color);
	PathNode() = default;
	~PathNode() = default;
};

