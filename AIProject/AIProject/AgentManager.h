#pragma once
#include "Headers.h"
#include "FSM.h"
#include "Boid.h"

class AgentManager
{
	vector <Boid>					
  m_agents;

	FSM m_stateMachine;

public:

	void 
  Initialize(vector <AgentData>& agents), Render(RenderWindow& window), Update(AgentManager& agents, float deltaTime);

	Boid* 
  GetAgentAt(unsigned int index);

	int 
	GetNumAgents();

	AgentManager() = default;
	~AgentManager() = default;
};

