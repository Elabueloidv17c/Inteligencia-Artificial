#pragma once
#include "WalkerBreadthFS.h"
#include "WalkerDijkstra.h"
#include "WalkerDepthFS.h"
#include "WalkerBestFS.h"
#include "WalkerAStar.h"
#include "GridMakerUI.h"
#include "Walker.h"
#include "Scene.h"
#include "Grid.h"

class PathFinding : public Scene {
	Vector2f						m_mousePosition;
	RectNode						m_nodeTypes;
	Grid								m_map;
	GridMakerUI					m_UI;
	Walker*							m_walker;
	WalkerDepthFS				m_depthFS;
	WalkerBreadthFS			m_breadthFS;
	WalkerBestFS				m_bestFS;
	WalkerDijkstra			m_dijkstra;
	WalkerAStar					m_AStar;

public:

	PathFinding();
	~PathFinding() = default;

	void								ProcessMessages(Event& event, RenderWindow& window);
	void								Initialize(Vector2f windowSize);
	void								Render(RenderWindow& window);
	void								ShutDown();
	void								Update();
};

