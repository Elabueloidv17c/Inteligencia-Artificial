#include "RunState.h"

void RunState::Init() {

}

EBehaviour RunState::Update(Boid& agent, float deltaTime) {
	return EBehaviour::Run;
}

void RunState::Delete() {
}
