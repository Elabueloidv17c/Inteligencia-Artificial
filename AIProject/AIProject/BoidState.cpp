#include "BoidState.h"

void BoidState::Init() {
}

EBehaviour BoidState::Update(Boid& boid, float deltaTime) {
	return EBehaviour::Idle;
}

void BoidState::Delete() {
}
