#include "SteeringBehaviour.h"
#include "SteeringForce.h"
#include "Agent.h"

namespace AIForGames {
	SteeringBehaviour::SteeringBehaviour() {};
	SteeringBehaviour::~SteeringBehaviour() {};

	// Calculate a force to add to the Agent
	void SteeringBehaviour::Update(Agent* agent, float deltaTime) {
		// Pass the Agent into the current SteeringForce's calculation function
		agent->AddForce(GetCurrentForce()->GetForce(agent));
	};

	SteeringForce* SteeringBehaviour::GetCurrentForce() { return currentForce; }
}