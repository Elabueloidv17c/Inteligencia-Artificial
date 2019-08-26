#pragma once
#include "Headers.h"
#include "Vector2.h"
#include "Timer.h"
#include "CircleObstacle.h"
#include "AgentManager.h"
#include "NodePlacer.h"
#include "PathNode.h"
#include "Path.h"
	
#include "Scene.h"
#include "GridNode.h"
#include "Grid.h"

class World {

	RenderWindow	m_window;
	Scene*				m_scene;
	Event					m_event;
	Timer					m_timer;

public:

	void					Initialize(WindowData window);
	void					CatchMessages();
	void					ShutDown();
	void					Update();
	void					Render();

	World() = default;
	~World() = default;
};	