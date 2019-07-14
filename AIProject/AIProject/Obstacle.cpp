#include "Obstacle.h"

Vector2* Obstacle::GetPosition() {
	return &m_position;
}

Obstacle::Obstacle(Vector2 position) {
	m_position = position;
}

Obstacle::~Obstacle() {
}
