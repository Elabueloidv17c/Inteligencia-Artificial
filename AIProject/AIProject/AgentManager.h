#pragma once
#include "Headers.h"
#include "Boid.h"

class AgentManager
{
	vector <Boid>					m_agents;

public:

	void Initialize(vector <AgentData>& agents);
	void Render(RenderWindow& window);
	void Update(float deltaTime);

	Boid* GetAgentAt(unsigned int index);

	AgentManager() = default;
	~AgentManager() = default;
};

