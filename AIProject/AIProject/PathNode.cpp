#include "PathNode.h"

PathNode::PathNode(Vector2 position, float size, float roadLimit, float friction, Color color) {
#ifdef DEBUG
	m_shape.setPosition(Vector2f(position.x, position.y));
	m_shape.setOrigin(Vector2f(roadLimit, roadLimit));
	m_shape.setFillColor(color);
	m_shape.setRadius(roadLimit);
#endif // DEBUG

	m_friction = friction;
	m_roadLimit = roadLimit;
	m_position = position;
	m_size = size;
}

const Vector2* 
PathNode::GetPosition() {
	return &m_position;
}

const float 
PathNode::GetSize() {
	return m_size;
}

const float
PathNode::GetFriction() {
	return m_friction;
}

const float
PathNode::GetRoadLimit() {
	return m_roadLimit;
}

const PathNode* 
PathNode::Get() {
	return this;
}


void PathNode::SetBounds(float size, float roadLimit, float friction) {
	
	m_roadLimit = roadLimit;
	m_size = size;
}

void PathNode::SetPosition(Vector2 position) {
	m_position = position;
}

#ifdef DEBUG
CircleShape* PathNode::GetShape() {
	return &m_shape;
}

void PathNode::SetColor(Color color) {
	m_shape.setFillColor(color);
}

void PathNode::SetShape(CircleShape shape) {
	m_shape = shape;
}
#endif // DEBUG