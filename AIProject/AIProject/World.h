#pragma once
#include "Headers.h"
#include "Vector2.h"
#include "Timer.h"
#include "AgentManager.h"
	
class World
{	
	AgentManager		m_agents;
	RenderWindow		m_window;
	Event				m_envent;
	Timer				m_timer;

	void				CatchMessages();

public:

	void				Initialize(WindowData window);
	void				Update();
	void				Render();

	World() = default;
	~World() = default;
};	