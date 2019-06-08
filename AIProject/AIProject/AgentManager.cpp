#include "AgentManager.h"

void AgentManager::Initialize(vector <AgentData>& agents)
{
	m_agents.resize(agents.size());

	for (int i = 0; i < m_agents.size(); i++)
	{
		if (!m_agents[i].Initialize(agents[i]))
		{
			cout << "Error: Texture for agent #" << (i + 1) << "  not loaded\n";
		}
	}
}

void AgentManager::Update(float deltaTime)
{
	for (int i = 0; i < m_agents.size(); i++)
	{
		m_agents[i].Update(deltaTime);
	}
}

Boid* AgentManager::GetAgentAt(unsigned int index)
{
	return &m_agents[index];
}

void AgentManager::Render(RenderWindow& window)
{
	for (int i = 0; i < m_agents.size(); i++)
	{
		m_agents[i].Render(window);
	}
}
