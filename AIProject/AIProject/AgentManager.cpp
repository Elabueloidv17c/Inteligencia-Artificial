#include "AgentManager.h"

void AgentManager::Initialize(vector <AgentData>& agents) {
	m_agents.resize(agents.size());

	for (int i = 0; i < m_agents.size(); i++) {
		if (!m_agents[i].Initialize(agents[i])) {
			cout << "Error: Texture for agent #" << (i + 1) << "  not loaded\n";
		}
	}
}

void AgentManager::Update(AgentManager& agents, float deltaTime) {
	for (int i = 0; i < m_agents.size(); i++) {
		//m_stateMachine.Update(m_agents[i], deltaTime);
		m_agents[i].Update(deltaTime);
	}
}

Boid* AgentManager::GetAgentAt(unsigned int index) {
	return &m_agents[index];
}

int 
AgentManager::GetNumAgents() {
	return m_agents.size();
}

void AgentManager::Render(RenderWindow& window) {
	for (int i = 0; i < m_agents.size(); i++) {
		m_agents[i].Render(window);
	}
}
