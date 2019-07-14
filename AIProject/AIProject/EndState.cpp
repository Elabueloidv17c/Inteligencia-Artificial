#include "EndState.h"

void EndState::Init() {
}

EBehaviour EndState::Update(Boid& agent, float deltaTime) {
	return EBehaviour::Idle;
}

void EndState::Delete() {
}
