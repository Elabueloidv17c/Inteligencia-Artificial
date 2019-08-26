#include "GridNode.h"

GridNode::GridNode() {
	m_nodes = nullptr;
	m_shape = nullptr;
	m_isDirty = nullptr;
}

GridNode::~GridNode() {
	Destroy();
}

GridNode::GridNode(
										bool* isDirty,
										RectNode* nodes,
										Vector2f	position,
										bool isObstacle,
										unsigned short cost,
										unsigned short column,
										unsigned short row
) {
	m_isDirty = isDirty;
	m_nodes = nodes;
	m_position = position;
	m_isObstacle = isObstacle;
	m_cost = cost;
	m_column = column;
	m_row = row;
}

void 
GridNode::Initialize(
													bool* isDirty,
													RectNode* nodes,
													Vector2f	position,
													bool isObstacle,
													unsigned short cost, 
													unsigned short column,
													unsigned short row
) {
	m_isDirty = isDirty;
	m_nodes = nodes;
	m_position = position;
	m_isObstacle = isObstacle;
	m_cost = cost;
	m_column = column;
	m_row = row;

	EButton defaultValue = EButton::Weight1;
	SetShape(defaultValue);
	
	m_bounds = Bounds(position, m_shape->getSize());
}

void 
GridNode::Render(RenderWindow& window) {
	m_shape->setPosition(m_position);
	window.draw(*m_shape);
}

void 
GridNode::Update(Vector2f& mousePosition, EButton& nodeType) {
	if (m_bounds.isColliding(mousePosition)) {
		SetShape(nodeType);
	}
}


void 
GridNode::Destroy() {
	m_nodes = nullptr;
	m_shape = nullptr;
}

void 
GridNode::SetShape(EButton& nodeType) {
	switch (nodeType)
	{
		case EButton::Obstacle: {
			m_shape = &m_nodes->obstacle;
			m_isObstacle = true;
			break;
		}
		case EButton::Weight1: {
			m_shape = &m_nodes->cost1;
			m_isObstacle = false;
			m_cost = 100;
			break;
		}
		case EButton::Weight2: {
			m_shape = &m_nodes->cost2;
			m_isObstacle = false;
			m_cost = 200;
			break;
		}
		case EButton::Weight3: {
			m_shape = &m_nodes->cost3;
			m_isObstacle = false;
			m_cost = 300;
			break;
		}
		case EButton::Weight4: {
			m_shape = &m_nodes->cost4;
			m_isObstacle = false;
			m_cost = 400;
			break;
		}
		case EButton::Weight5: {
			m_shape = &m_nodes->cost5;
			m_isObstacle = false;
			m_cost = 500;
			break;
		}
	}
}

bool 
GridNode::IsIn(const vector<NodeRevision>& nodes, int& index) {
	for (int i = 0; i < nodes.size(); i++){
		if (nodes[i].row == m_row && nodes[i].column == m_column) {
			index = i;
			return true;
		}
	}
	index = -1;
	return false;
}

bool
GridNode::IsIn(const vector<NodeRevision>& nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].row == m_row && nodes[i].column == m_column) {
			return true;
		}
	}
	return false;
}

const unsigned short
GridNode::GetColumn() {
	return m_column;
}

const unsigned short 
GridNode::GetRow() {
	return m_row;
}

void 
GridNode::SetPosition(Vector2f position) {
	m_position = position;
	*m_isDirty = true;
}

void 
GridNode::SetWeight(unsigned short cost) {
	m_cost = cost;
	*m_isDirty = true;
}

void 
GridNode::SetIsObstacle(bool state) {
	m_isObstacle = state;
	*m_isDirty = true;
}

Vector2f 
GridNode::GetSize() {
	return m_shape->getSize();
}

const unsigned short*
GridNode::GetWeight() {
	return &m_cost;
}

const bool* 
GridNode::GetIsObstacle() {
	return &m_isObstacle;
}

const Vector2f* 
GridNode::GetPosition() {
	return &m_position;
}

const Vector2f* 
GridNode::GetCenter() {
	return &m_shape->getOrigin();
}

const RectangleShape* 
GridNode::GetShape() {
	return m_shape;
}

Bounds* GridNode::GetBounds() {
	return &m_bounds;
}
