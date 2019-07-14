#include "FSM.h"

void FSM::Init() {

}

void FSM::Update(Boid& agent, float deltaTime)
{
	switch (*agent.GetCurrentState())
	{
	case EBehaviour::Run:
	{
		agent.SetCurrentState(m_run.Update(agent, deltaTime));
		break;
	}
	case EBehaviour::End:
	{
		agent.SetCurrentState(m_end.Update(agent, deltaTime));
		break;
	}
	default:
		agent.SetCurrentState(EBehaviour::Idle);
		break;
	}
}

void FSM::Delete()
{
}
