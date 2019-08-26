#pragma once
#include "UserInterface.h"
#include "Button.h"
#include "Walker.h"

class GridMakerUI : public UserInterface {

	RectNode*									m_nodeTypes;
	CircleNode*								m_stepTypes;
	
	EButton										m_button;

	Button										m_obstacle;
	Button										m_weight1;
	Button										m_weight2;
	Button										m_weight3;
	Button										m_weight4;
	Button										m_weight5;

	Button										m_objective;
	Button										m_origin;

	Button										m_start;
	Button										m_stop;

	Button										m_bestFS;
	Button										m_depthFS;
	Button										m_breadthFS;
	Button										m_dijkstra;
	Button										m_AStar;

	Button										m_distance;
	Button										m_sqrtDistance;
	Button										m_manhattanDistance;
	Button										m_cheapest;

	RectangleShape						m_backGround;
	Vector2f									m_position;
	Vector2f									m_size;

public:

	EButton*									GetActiveButton();
	void											SetActiveButton(EButton button);

	void											Initialize(Color color, Vector2f position, Vector2f size, RectNode* nodeTypes, CircleNode* stepTypes);
	void											Render(RenderWindow& window);
	void											Update(Vector2f& position, Walker& walker);
	void											ShutDown();

	GridMakerUI();
	~GridMakerUI();
};

