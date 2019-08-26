#include "PathFinding.h"

PathFinding::PathFinding() {

}

void
PathFinding::ProcessMessages(Event& event, RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		m_mousePosition = (sf::Vector2f) sf::Mouse::getPosition(window);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		m_UI.SetActiveButton(EButton::Weight1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_UI.SetActiveButton(EButton::Weight2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		m_UI.SetActiveButton(EButton::Weight3);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		m_UI.SetActiveButton(EButton::Weight4);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		m_UI.SetActiveButton(EButton::Weight5);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		m_UI.SetActiveButton(EButton::Obstacle);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_UI.SetActiveButton(EButton::Origin);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_UI.SetActiveButton(EButton::Objective);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || Event::Closed == event.type) {
		window.close();
	}
	else if (Event::Resized == event.type) {
		window.setSize(Vector2u(event.size.width, event.size.height));
		window.setView(View(FloatRect(0, 0, event.size.width, event.size.height)));
	}
}

void 
PathFinding::Initialize(Vector2f windowSize) {
	m_map.Initialize(100, 72, Vector2f(10, 10));
	m_depthFS.Initialize(&m_map);
	m_breadthFS.Initialize(&m_map);
	m_bestFS.Initialize(&m_map);
	m_dijkstra.Initialize(&m_map);
	m_AStar.Initialize(&m_map);
	m_walker = &m_depthFS;

	m_UI.Initialize(Color(127, 32, 32, 255), Vector2f((float) m_map.GetBounds()->right, (float)m_map.GetBounds()->top), 
	Vector2f(windowSize.x - m_map.GetBounds()->right, windowSize.y - m_map.GetBounds()->top), m_map.GetRectNode(), m_walker->GetCircleNode());
}

void 
PathFinding::ShutDown() {

}

void 
PathFinding::Update() {
	m_UI.Update(m_mousePosition, *m_walker);
	m_map.Update(m_mousePosition, *m_UI.GetActiveButton());

	if (*m_UI.GetActiveButton() == EButton::Depth) {
		m_UI.SetActiveButton(EButton::Obstacle);
		m_walker = &m_depthFS;
	}
	if (*m_UI.GetActiveButton() == EButton::Breadth) {
		m_UI.SetActiveButton(EButton::Obstacle);
		m_walker = &m_breadthFS;
	}
	if (*m_UI.GetActiveButton() == EButton::Best) {
		m_UI.SetActiveButton(EButton::Obstacle);
		m_walker = &m_bestFS;
	}
	if (*m_UI.GetActiveButton() == EButton::Dijkstra) {
		m_UI.SetActiveButton(EButton::Obstacle);
		m_walker = &m_dijkstra;
	}
	if (*m_UI.GetActiveButton() == EButton::AStar) {
		m_UI.SetActiveButton(EButton::Obstacle);
		m_walker = &m_AStar;
	}
	if (*m_UI.GetActiveButton() == EButton::EuclidianDist) {
		m_walker->SetHeuristic(*m_UI.GetActiveButton());
		m_UI.SetActiveButton(EButton::Obstacle);
	}
	if (*m_UI.GetActiveButton() == EButton::SqrtDist) {
		m_walker->SetHeuristic(*m_UI.GetActiveButton());
		m_UI.SetActiveButton(EButton::Obstacle);
	}
	if (*m_UI.GetActiveButton() == EButton::CityDist) {
		m_walker->SetHeuristic(*m_UI.GetActiveButton());
		m_UI.SetActiveButton(EButton::Obstacle);
	}
	if (*m_UI.GetActiveButton() == EButton::CheapestNode) {
		m_walker->SetHeuristic(*m_UI.GetActiveButton());
		m_UI.SetActiveButton(EButton::Obstacle);
	}
	m_walker->Update(m_mousePosition, *m_UI.GetActiveButton());
}

void 
PathFinding::Render(RenderWindow& window) {
	m_map.Render(window);
	m_UI.Render(window);
	m_walker->Render(window);
}
