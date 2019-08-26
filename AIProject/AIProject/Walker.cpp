#include "Walker.h"

ESearchState 
Walker::Search() {
	return ESearchState::NoPath;
}

unsigned int
Walker::EvaluateNeighbors() {
	return 0;
}

void 
Walker::Update(Vector2f& mousePosition, EButton& activeButton) {
	if (m_bounds.isColliding(mousePosition)) {
		if (activeButton == EButton::Origin) {
			SetOrigin(mousePosition);
		}
		if (activeButton == EButton::Objective) {
			SetDestination(mousePosition);
		}
	}
	if (m_state == StillSearching) {
		m_state = Search();
	}
	mousePosition.x = -1;
}

void 
Walker::Render(RenderWindow& window) {
	for (int i = 0; i < m_open.size(); i++) {
		m_open[i].visualState->setPosition(m_open[i].position);
		window.draw(*m_open[i].visualState);
	}
	for (int i = 0; i < m_closed.size(); i++) {
		m_closed[i].visualState->setPosition(m_closed[i].position);
		window.draw(*m_closed[i].visualState);
	}
	for (int i = 0; i < m_path.size(); i++) {
		m_path[i].visualState->setPosition(m_path[i].position);
		window.draw(*m_path[i].visualState);
	}
	if (m_origin) {
		window.draw(m_step.origin);
	}
	if (m_destination) {
		window.draw(m_step.destination);
	}
}

void 
Walker::Initialize(Grid* grid) {
	m_state = NoPath;
	m_destination = nullptr;
	m_origin = nullptr;
	m_heuristic = Cheapest;
	m_map = grid->GetMap();
	m_bounds = *grid->GetBounds();
	m_step = CircleNode(Color(), 1.0f, m_map[0][0][0].GetSize());
}

void 
Walker::Start() {
	if (m_state != StillSearching) {
		m_state = StillSearching;
	}

	m_open.clear();
	if (m_origin) {
		m_open.push_back(NodeRevision(m_origin->GetPosition(), m_origin, nullptr, &m_step.open));
	}
	m_path.clear();
	m_closed.clear();
}

void 
Walker::Stop() {
	if (m_state == StillSearching) {
		m_state = NoPath;
	}

	m_open.clear();
	m_path.clear();
	m_closed.clear();
}

CircleNode*
Walker::GetCircleNode() {
	return &m_step;
}

void 
Walker::CheckNeighbor(NodeRevision& node, short offsetY, short offsetX) {

}

unsigned int 
Walker::LightestNode() {
	return 0;
}

unsigned int 
Walker::ManhattanDistance() {
	return 0;
}

unsigned int 
Walker::EuclideanDistance() {
	return 0;
}

unsigned int 
Walker::QuadraticDistance() {
	return 0;
}

void
Walker::SetDestination(Vector2f& position) {
	if (m_map) {
		for (int i = 0; i < m_map[0].size(); i++) {
			for (int j = 0; j < m_map[0][i].size(); j++) {
				if (m_map[0][i][j].GetBounds()->isColliding(position)) {
					m_destination = &m_map[0][i][j];
					m_step.destination.setPosition(*m_destination->GetPosition());
					return;
				}
			}
		}
	}
}

void
Walker::SetOrigin(Vector2f& position) {
	if (m_state == StillSearching) {
		m_state = NoPath;
	}
	m_open.clear();
	m_closed.clear();
	m_path.clear();
	if (m_map) {
		for (int i = 0; i < m_map[0].size(); i++) {
			for (int j = 0; j < m_map[0][i].size(); j++) {
				if (m_map[0][i][j].GetBounds()->isColliding(position)) {
					m_origin = &m_map[0][i][j];
					m_step.origin.setPosition(*m_origin->GetPosition());
					m_open.clear();
					m_open.push_back(NodeRevision(m_map[0][i][j].GetPosition(), &m_map[0][i][j], nullptr, &m_step.open, 0));
					return;
				}
			}
		}
	}
}

void 
Walker::SetHeuristic(EButton& type) {
	switch (type)
	{
	case EButton::CheapestNode:
	{
		m_heuristic = EHeuristic::Cheapest;
		break;
	}
	case EButton::EuclidianDist:
	{
		m_heuristic = EHeuristic::Distance;
		break;
	}
	case EButton::SqrtDist:
	{
		m_heuristic = EHeuristic::SqrtDistance;
		break;
	}
	case EButton::CityDist:
	{
		m_heuristic = EHeuristic::Manhatan;
		break;
	}
	}
}

Walker::Walker(Grid* grid) {
	
	m_state = NoPath;

	m_destination = nullptr;
	m_origin = nullptr;

	m_bounds = *grid->GetBounds();
	m_map = grid->GetMap();

	m_step = CircleNode(Color(), 1.0f, m_map[0][0][0].GetSize());
}

Walker::~Walker() {

}
