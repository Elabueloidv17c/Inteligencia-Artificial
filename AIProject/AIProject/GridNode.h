#pragma once
#include "Headers.h"
#include "Walker.h"

class Grid;
struct NodeRevision;

class GridNode {
	
	RectNode*									m_nodes;
	RectangleShape*						m_shape;
	
	Vector2f									m_position;
	Bounds										m_bounds;

	bool*											m_isDirty;
	bool											m_isObstacle;
	unsigned short						m_cost;

	unsigned short						m_column;
	unsigned short						m_row;

public:

	void											Render(RenderWindow& window);
	void											Update(Vector2f& mousePosition, EButton& nodeType);

	void											Initialize(
																				bool* isDirty,
																				RectNode* shapes,
																				Vector2f	position, 
																				bool isObstacle,
																				unsigned short cost,
																				unsigned short column,
																				unsigned short row
																			);

	void											Destroy();

	void											SetPosition(Vector2f	position);
	void											SetWeight(unsigned short	cost);
	void											SetIsObstacle(bool state);
	void											SetShape(EButton& nodeType);

	bool											IsIn(const vector<NodeRevision>& nodes, int& index);
	bool											IsIn(const vector<NodeRevision>& nodes);

	const unsigned short			GetColumn();
	const unsigned short			GetRow();
	Vector2f									GetSize();
	const unsigned short*			GetWeight();
	const bool*								GetIsObstacle();
	const Vector2f*						GetPosition();
	const Vector2f*						GetCenter();
	const RectangleShape*			GetShape();
	Bounds*										GetBounds();

	GridNode(
						bool* isDirty,
						RectNode* shapes,
						Vector2f	position,
						bool isObstacle,
						unsigned short cost,
						unsigned short column,
						unsigned short row
	);

	GridNode();
	~GridNode();
};

struct NodeRevision {
	Vector2f												position;
	GridNode*												reference;
	CircleShape*										visualState;
	NodeRevision*										parent;
	unsigned short									column;
	unsigned short									row;
	unsigned int										cost;
	unsigned int										costD;
	unsigned int										costW;

	NodeRevision() {}

	NodeRevision(const Vector2f* position, GridNode* node, NodeRevision* parent, CircleShape* circle, unsigned int cost) {
		this->position = *position;
		this->parent = parent;
		reference = node;
		visualState = circle;
		column = node->GetColumn();
		row = node->GetRow();
		this->cost = cost;
	}

	NodeRevision(const Vector2f* position, GridNode* node, NodeRevision* parent, CircleShape* circle, unsigned int costD, unsigned int costW) {
		this->position = *position;
		this->parent = parent;
		reference = node;
		visualState = circle;
		column = node->GetColumn();
		row = node->GetRow();
		this->costD = costD;
		this->costW += parent->cost;
		this->cost = costD + costW;
	}

	NodeRevision(const Vector2f* position, GridNode* node, NodeRevision* parent, CircleShape* circle) {
		this->position = *position;
		this->parent = parent;
		this->cost = 0;
		reference = node;
		visualState = circle;
		column = node->GetColumn();
		row = node->GetRow();
	}
};