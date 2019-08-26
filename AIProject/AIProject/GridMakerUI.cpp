#include "GridMakerUI.h"

void 
GridMakerUI::SetActiveButton(EButton button) {
	m_button = button;
}

void 
GridMakerUI::Initialize(Color color, Vector2f position, Vector2f size, RectNode* nodeTypes, CircleNode* stepTypes) {
	m_position = position;
	m_nodeTypes = nodeTypes;
	m_stepTypes = stepTypes;

	m_backGround.setPosition(m_position);
	m_backGround.setFillColor(color);
	m_backGround.setSize(Vector2f(size.x, size.y));

	m_button = EButton::Obstacle;

	m_fonts.push_back(sf::Font());
	if (!m_fonts[0].loadFromFile("..\\Fonts\\Stanwick.otf")) {
		return;
	}

	//------------------------------------------------------------------------------------------------------------
	//Action Buttons
	//------------------------------------------------------------------------------------------------------------
	m_start.Initialize(Color(200, 200, 200, 255), Color(0, 127, 0, 255), &m_fonts[0], "Start", 32,
	Vector2f(1010, 660), Vector2f(110, 50));

	m_depthFS.Initialize(Color(200, 200, 200, 255), color, &m_fonts[0], "DepthFS", 20,
	Vector2f(1010, 620), Vector2f(110, 30));
	
	m_breadthFS.Initialize(Color(200, 200, 200, 255), color, &m_fonts[0], "BreadthFS", 20,
	Vector2f(1010, 560), Vector2f(110, 30));

	m_bestFS.Initialize(Color(200, 200, 200, 255), color, &m_fonts[0], "BestFS", 20,
	Vector2f(1010, 500), Vector2f(110, 30));

	m_dijkstra.Initialize(Color(200, 200, 200, 255), color, &m_fonts[0], "Dijkstra", 20,
	Vector2f(1010, 440), Vector2f(110, 30));

	m_AStar.Initialize(Color(200, 200, 200, 255), color, &m_fonts[0], "A*", 20,
	Vector2f(1010, 390), Vector2f(110, 30));

	m_stop.Initialize(Color(200, 200, 200, 255), Color(0, 127, 0, 255), &m_fonts[0], "Stop", 32,
	Vector2f(1140, 660), Vector2f(110, 50));

	m_manhattanDistance.Initialize(Color(200, 200, 200, 255), Color(), &m_fonts[0], "City Dist", 20,
	Vector2f(1140, 440), Vector2f(130, 30));
	
	m_sqrtDistance.Initialize(Color(200, 200, 200, 255), Color(), &m_fonts[0], "Square Dist", 20,
	Vector2f(1140, 560), Vector2f(130, 30));

	m_distance.Initialize(Color(200, 200, 200, 255), Color(), &m_fonts[0], "Euclidean Dist", 20,
	Vector2f(1140, 500), Vector2f(130, 30));

	m_cheapest.Initialize(Color(200, 200, 200, 255), Color(), &m_fonts[0], "Lightest Node", 20,
	Vector2f(1140, 390), Vector2f(130, 30));

	//------------------------------------------------------------------------------------------------------------
	//Build Buttons
	//------------------------------------------------------------------------------------------------------------
	Vector2f Size = Vector2f(nodeTypes->cost1.getSize().x * 2, nodeTypes->cost1.getSize().y * 2);

	m_obstacle.Initialize(nodeTypes->obstacle.getFillColor(), Color(), nullptr, "", 0, Vector2f(1010, 10), Size);
	m_weight1.Initialize(nodeTypes->cost1.getFillColor(), Color(), nullptr, "", 0, Vector2f(1050, 10), Size);
	m_weight2.Initialize(nodeTypes->cost2.getFillColor(), Color(), nullptr, "", 0, Vector2f(1090, 10), Size);
	m_weight3.Initialize(nodeTypes->cost3.getFillColor(), Color(), nullptr, "", 0, Vector2f(1130, 10), Size);
	m_weight4.Initialize(nodeTypes->cost4.getFillColor(), Color(), nullptr, "", 0, Vector2f(1170, 10), Size);
	m_weight5.Initialize(nodeTypes->cost5.getFillColor(), Color(), nullptr, "", 0, Vector2f(1210, 10), Size);

	m_origin.Initialize(stepTypes->origin.getFillColor(), Color(), nullptr, "", 0, 
	Vector2f(1010, 60), stepTypes->origin.getRadius() * 2);
	
	m_objective.Initialize(stepTypes->destination.getFillColor(), Color(), nullptr, "", 0, 
	Vector2f(1050, 60), stepTypes->destination.getRadius() * 2);
}

void GridMakerUI::ShutDown() {

}

void GridMakerUI::Update(Vector2f& mousePosition, Walker& walker) {

	if (m_obstacle.IsPressed(mousePosition)) {
		m_button = EButton::Obstacle;
		mousePosition.x = -1;
	}
	else if (m_weight1.IsPressed(mousePosition)) {
		m_button = EButton::Weight1;
		mousePosition.x = -1;
	}
	else if (m_weight2.IsPressed(mousePosition)) {
		m_button = EButton::Weight2;
		mousePosition.x = -1;
	}
	else if (m_weight3.IsPressed(mousePosition)) {
		m_button = EButton::Weight3;
		mousePosition.x = -1;
	}
	else if (m_weight4.IsPressed(mousePosition)) {
		m_button = EButton::Weight4;
		mousePosition.x = -1;
	}
	else if (m_weight5.IsPressed(mousePosition)) {
		m_button = EButton::Weight5;
		mousePosition.x = -1;
	}
	else if (m_origin.IsPressed(mousePosition)) {
		m_button = EButton::Origin;
		mousePosition.x = -1;
	}
	else if (m_objective.IsPressed(mousePosition)) {
		m_button = EButton::Objective;
		mousePosition.x = -1;
	}
	else if (m_breadthFS.IsPressed(mousePosition)) {
		m_button = EButton::Breadth;
		mousePosition.x = -1;
	}
	else if (m_depthFS.IsPressed(mousePosition)) {
		m_button = EButton::Depth;
		mousePosition.x = -1;
	}
	else if (m_bestFS.IsPressed(mousePosition)) {
		m_button = EButton::Best;
		mousePosition.x = -1;
	}
	else if (m_distance.IsPressed(mousePosition)) {
		m_button = EButton::EuclidianDist;
		mousePosition.x = -1;
	}
	else if (m_sqrtDistance.IsPressed(mousePosition)) {
		m_button = EButton::SqrtDist;
		mousePosition.x = -1;
	}
	else if (m_dijkstra.IsPressed(mousePosition)) {
		m_button = EButton::Dijkstra;
		mousePosition.x = -1;
	}
	else if (m_AStar.IsPressed(mousePosition)) {
		m_button = EButton::AStar;
		mousePosition.x = -1;
	}
	else if (m_manhattanDistance.IsPressed(mousePosition)) {
		m_button = EButton::CityDist;
		mousePosition.x = -1;
	}
	else if (m_cheapest.IsPressed(mousePosition)) {
		m_button = EButton::CheapestNode;
		mousePosition.x = -1;
	}
	else if (m_start.IsPressed(mousePosition)) {
		walker.Start();
		mousePosition.x = -1;
	}
	else if (m_stop.IsPressed(mousePosition)) {
		walker.Stop();
		mousePosition.x = -1;
	}
}

EButton* GridMakerUI::GetActiveButton() {
	return &m_button;
}

void GridMakerUI::Render(RenderWindow& window) {
	window.draw(m_backGround);

	m_obstacle.Render(window);
	m_weight1.Render(window);
	m_weight2.Render(window);
	m_weight3.Render(window);
	m_weight4.Render(window);
	m_weight5.Render(window);

	m_objective.Render(window);
	m_origin.Render(window);

	m_depthFS.Render(window);
	m_breadthFS.Render(window);
	m_bestFS.Render(window);
	m_dijkstra.Render(window);
	m_AStar.Render(window);

	m_distance.Render(window);
	m_sqrtDistance.Render(window);
	m_manhattanDistance.Render(window);
	m_cheapest.Render(window);

	m_start.Render(window);
	m_stop.Render(window);
}

GridMakerUI::GridMakerUI() {

}

GridMakerUI::~GridMakerUI() {

}
