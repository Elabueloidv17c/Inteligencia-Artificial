#pragma once
#include "Headers.h"

class Obstacle
{
	Vector2			m_position;

public:
	Obstacle(Vector2 position);
	Obstacle() = default;
	virtual ~Obstacle();

	Vector2* GetPosition();
};

