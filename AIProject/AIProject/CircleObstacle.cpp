#include "CircleObstacle.h"

CircleObstacle::CircleObstacle(Vector2 position, float radius, Color color) : Obstacle(position){
#ifdef DEBUG
	m_shape.setPosition(Vector2f(position.x, position.y));
	m_shape.setOrigin(Vector2f(radius, radius));
	m_shape.setFillColor(color);
	m_shape.setRadius(radius);
#endif // DEBUG

	m_radius = radius;
}

CircleObstacle::~CircleObstacle() {
}

const float* CircleObstacle::GetRadius() {
	return &m_radius;
}

#ifdef DEBUG
CircleShape* CircleObstacle::GetShape() {
	return &m_shape;
}

void CircleObstacle::SetColor(Color color) {
	m_shape.setFillColor(color);
}

void CircleObstacle::SetShape(CircleShape shape) {
	m_shape = shape;
}
#endif // DEBUG