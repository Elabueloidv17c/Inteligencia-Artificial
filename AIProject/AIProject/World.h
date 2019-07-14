#pragma once
#include "Headers.h"
#include "Vector2.h"
#include "Timer.h"
#include "CircleObstacle.h"
#include "AgentManager.h"
#include "NodePlacer.h"
#include "PathNode.h"
#include "Path.h"
	
class World
{	
	AgentManager		
	m_agents;
	
	vector <Path>
	m_paths;

	vector <CircleObstacle>
	m_obstacles;

	NodePlacer
	m_levelDesigner;

	RenderWindow		
	m_window;
	
	Event						
	m_envent;

	Timer						
	m_timer;

	Texture
	m_backGroundexture;

	Sprite
	m_backgroundSprite;

	void				CatchMessages();

public:

	void				Initialize(WindowData window);
	void				Update();
	void				Render();

	World() = default;
	~World() = default;
};	