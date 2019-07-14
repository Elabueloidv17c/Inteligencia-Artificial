#pragma once
#include "Headers.h"
#include "BoidState.h"

class EndState : public BoidState
{
public:
	void Init();
	EBehaviour Update(Boid& agent, float deltaTime);
	void Delete();

	EndState() = default;
	~EndState() = default;
};

