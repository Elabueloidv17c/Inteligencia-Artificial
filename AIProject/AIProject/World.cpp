#include "World.h"

void World::Initialize(WindowData window)
{
	m_window.create(VideoMode(window.width, window.heigh), window.name, window.style);

	vector <AgentData> agents;
	
	agents.push_back(AgentData{
	"..\\Textures\\zerg.png",				//texturePath
	Vector2(900, 400), 						//position
	Vector2(1.0f, 0.5f), 					//direction
	35.0f, 									//acceleration
	50.0f, 									//speed
	0.1f, 									//mass
	1.0f, 									//waitTime
	1.0f,									//seekMagnitude
	1.0f,									//fleeMagnitude
	50.0f,									//arriveMagnitude
	4.0f,									//pursueMagnitude
	3.0f,									//evadeMagnitude
	0.0f,									//wanderMagnitude
	0.0f,									//wanderTimeMagnitude
	0.0f,									//wanderRandomMagnitude
	});
	agents.push_back(AgentData{
	"..\\Textures\\zerg.png",				//texturePath
	Vector2(1000, 560), 					//position
	Vector2(0.2f, 0.5f), 					//direction
	40.0f, 									//acceleration
	60.0f, 									//speed
	0.5f, 									//mass
	1.5f, 									//waitTime
	2.0f,									//seekMagnitude
	4.0f,									//fleeMagnitude
	1.0f,									//arriveMagnitude
	2.0f,									//pursueMagnitude
	40.0f,									//evadeMagnitude
	0.0f,									//wanderMagnitude
	0.0f,									//wanderTimeMagnitude
	0.0f,									//wanderRandomMagnitude
	});
	agents.push_back(AgentData{
	"..\\Textures\\marine.png",				//texturePath
	Vector2(100, 100), 						//position
	Vector2(1.0f, 0.5f), 					//direction
	30.0f, 									//acceleration
	40.0f, 									//speed
	0.8f, 									//mass
	3.0f, 									//waitTime
	20.0f,									//seekMagnitude
	15.0f,									//fleeMagnitude
	10.0f,									//arriveMagnitude
	20.0f,									//pursueMagnitude
	30.0f,									//evadeMagnitude
	50.0f,									//wanderMagnitude
	0.0f,									//wanderTimeMagnitude
	0.0f,									//wanderRandomMagnitude
	});
	agents.push_back(AgentData{
	"..\\Textures\\marine.png",				//texturePath
	Vector2(600, 350), 						//position
	Vector2(0.0f, 0.0f), 					//direction
	0.0f, 									//acceleration
	0.0f, 									//speed
	0.0f, 									//mass
	0.0f, 									//waitTime
	0.0f,									//seekMagnitude
	0.0f,									//fleeMagnitude
	0.0f,									//arriveMagnitude
	0.0f,									//pursueMagnitude
	0.0f,									//evadeMagnitude
	0.0f,									//wanderMagnitude
	0.0f,									//wanderTimeMagnitude
	0.0f,									//wanderRandomMagnitude
	});
	agents.push_back(AgentData{
	"..\\Textures\\zealot.png",				//texturePath
	Vector2(800, 500), 						//position
	Vector2(1.0f, 0.5f), 					//direction
	10.0f, 									//acceleration
	20.0f, 									//speed
	0.1f, 									//mass
	1.0f, 									//waitTime
	60.0f,									//seekMagnitude
	1.0f,									//fleeMagnitude
	0.0f,									//arriveMagnitude
	4.0f,									//pursueMagnitude
	3.0f,									//evadeMagnitude
	0.0f,									//wanderMagnitude
	0.0f,									//wanderTimeMagnitude
	0.0f,									//wanderRandomMagnitude
	});
	agents.push_back(AgentData{
	"..\\Textures\\zealot.png",				//texturePath
	Vector2(400, 500), 						//position
	Vector2(1.0f, 0.5f), 					//direction
	40.0f, 									//acceleration
	60.0f, 									//speed
	0.1f, 									//mass
	1.0f, 									//waitTime
	1.0f,									//seekMagnitude
	1.0f,									//fleeMagnitude
	50.0f,									//arriveMagnitude
	60.0f,									//pursueMagnitude
	3.0f,									//evadeMagnitude
	0.0f,									//wanderMagnitude
	0.0f,									//wanderTimeMagnitude
	0.0f,									//wanderRandomMagnitude
	});
	agents.push_back(AgentData{
	"..\\Textures\\hydralisk.png",			//texturePath
	Vector2(500, 500), 						//position
	Vector2(1.0f, 0.5f), 					//direction
	30.0f, 									//acceleration
	50.0f, 									//speed
	0.1f, 									//mass
	1.0f, 									//waitTime
	40.0f,									//seekMagnitude
	50.0f,									//fleeMagnitude
	50.0f,									//arriveMagnitude
	60.0f,									//pursueMagnitude
	3.0f,									//evadeMagnitude
	0.0f,									//wanderMagnitude
	0.0f,									//wanderTimeMagnitude
	0.0f,									//wanderRandomMagnitude
	});
	agents.push_back(AgentData{
	"..\\Textures\\overlord.png",			//texturePath
	Vector2(1000, 500),						//position
	Vector2(1.0f, 0.5f), 					//direction
	30.0f, 									//acceleration
	80.0f, 									//speed
	0.1f, 									//mass
	5.0f, 									//waitTime
	40.0f,									//seekMagnitude
	50.0f,									//fleeMagnitude
	50.0f,									//arriveMagnitude
	60.0f,									//pursueMagnitude
	3.0f,									//evadeMagnitude
	0.0f,									//wanderMagnitude
	50.0f,									//wanderTimeMagnitude
	0.0f,									//wanderRandomMagnitude
	});


	m_agents.Initialize(agents);

	m_agents.GetAgentAt(0)->SetArriveObjective(m_agents.GetAgentAt(3));
	m_agents.GetAgentAt(1)->SetEvadeObjective(m_agents.GetAgentAt(4));
	m_agents.GetAgentAt(4)->SetSeekObjective(m_agents.GetAgentAt(1));
	m_agents.GetAgentAt(5)->SetPursueObjective(m_agents.GetAgentAt(2));
	m_agents.GetAgentAt(6)->SetSeekObjective(m_agents.GetAgentAt(5));
	m_agents.GetAgentAt(6)->SetFleeObjective(m_agents.GetAgentAt(5));

	m_timer.Start();
}

void World::CatchMessages()
{
	while (m_window.pollEvent(m_envent))
	{
		if (Event::MouseMoved)
		{
			m_agents.GetAgentAt(3)->SetPosition(m_envent.mouseMove.x, m_envent.mouseMove.y);
		}
		if (Event::Closed == m_envent.type)
		{
			m_window.close();
		}
		if (m_envent.type == Event::Resized)
		{
			FloatRect newSize(0, 0, m_envent.size.width, m_envent.size.height);
			m_window.setView(View(newSize));
		}
	}
}

void World::Update()
{
	while (m_window.isOpen())
	{
		CatchMessages();

		m_agents.Update(m_timer.GetDeltaTime());
		
		Render();
	}
}

void World::Render()
{
	//Clear screen
	m_window.clear();

	//Prepare frame
	m_agents.Render(m_window);

	//Present frame
	m_window.display();
}
