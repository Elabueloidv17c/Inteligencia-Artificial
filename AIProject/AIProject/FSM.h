#pragma once
#include "Headers.h"
#include "RunState.h"
#include "EndState.h"
#include "Boid.h"

class FSM
{
	RunState		m_run;
	EndState		m_end;

public:
	void Init();
	void Update(Boid& agent, float deltaTime);
	void Delete();
};

