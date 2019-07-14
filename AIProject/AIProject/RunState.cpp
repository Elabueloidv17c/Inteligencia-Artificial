#include "RunState.h"

void RunState::Init() {

}

EBehaviour RunState::Update(Boid& agent, float deltaTime) {
	
	*agent.GetSteeringForce() = Vector2();

	*agent.GetCurrentSpeed() += *agent.GetAcceleration() * deltaTime;

	if (*agent.GetCurrentSpeed() > *agent.GetSpeed()) {
		*agent.GetCurrentSpeed() = *agent.GetSpeed();
	}

	if (agent.GetPath()) {
		*agent.GetSteeringForce() += agent.FollowCircuit(*agent.GetPosition(), *agent.GetPath(), *agent.GetCurrentPathNode(), 
		*agent.GetCurrentSpeed(), *agent.GetCourseCorrection(), *agent.GetPathMagnitude(), deltaTime);
	}
	if (agent.GetParent()) {
		*agent.GetSteeringForce() += agent.Separation(*agent.GetPosition(), *agent.GetParent(), *agent.GetSeparationRadius(),
		*agent.GetSeparationMagnitude()) * (*agent.GetCurrentSpeed() / *agent.GetSpeed());
	}
	if (agent.GetObstacles()) {
		*agent.GetSteeringForce() += agent.ObstacleAvoidance(*agent.GetPosition(), *agent.GetDirection(), *agent.GetObstacleVision(),
		agent.GetClosestObstacle(*agent.GetPosition(), *agent.GetObstacleDetectionRadius(), agent.GetObstacles()), 
		*agent.GetObstacleAvoidanceMagnitude());
	}

	//------------------------------------------------------------------------------------------------------------------
	//CALCULATING NEW DIRECTION
	//------------------------------------------------------------------------------------------------------------------
	if (agent.GetSteeringForce()->Magnitude() > 0) {
		*agent.GetSteeringDirection() = (*agent.GetSteeringForce() - *agent.GetDirection()) * *agent.GetMass();
		*agent.GetDirection() += *agent.GetSteeringDirection() * deltaTime;
		agent.GetDirection()->Normalize();

		agent.GetSteeringForce()->Truncated(*agent.GetCurrentSpeed());
		*agent.GetPosition() += *agent.GetDirection() * agent.GetSteeringForce()->Magnitude() * deltaTime;
	}

	if (*agent.GetCurrentLap() >= 3) {
		return EBehaviour::End;
	}
	return EBehaviour::Run;
}

void RunState::Delete() {
}
