#pragma once
#include "Headers.h"
#include "BoidState.h"

class RunState : public BoidState
{
public:
	void Init();
	EBehaviour Update(Boid& agent, float deltaTime);
	void Delete();

	RunState() = default;
	~RunState() = default;
};

