#pragma once
#include "Headers.h"
#include "Boid.h"

class BoidState
{
protected:
	virtual void Init();
	virtual EBehaviour Update(Boid& boid, float deltaTime);
	virtual void Delete();

	BoidState() = default;
	~BoidState() = default;
};