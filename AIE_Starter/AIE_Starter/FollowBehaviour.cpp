#include "FollowBehaviour.h"
#include "Agent.h"

namespace AIForGames {
	FollowBehaviour::FollowBehaviour() {};
	FollowBehaviour::~FollowBehaviour() {};

	void FollowBehaviour::Update(Agent* agent, float deltaTime) {		
		// Retrieve a reference to the target agent
		Agent* target = agent->GetTarget();

		// Check the distance between our position and the target agent's current position
		float distance = glm::distance(target->GetPosition(), lastTargetPosition);

		// If the distance differs by more than one node, re-calculate the path
		if (distance > AIForGames::sizeOfCell) {
			lastTargetPosition = target->GetPosition();
			agent->GoTo(lastTargetPosition);
		}

		if (agent->GetType() == Agent::UtilityAI) {
			agent->SetStateText("UAI Following\n\tBehaviour refresh per 3 sec\n\tFollow to last known");
		}

		else if (agent->GetType() == Agent::FiniteStateMachine) {
			agent->SetStateText("FSM Following\n\tBehaviour refresh per 1 sec\n\tFollow to last known");
		}

		else {
			agent->SetStateText("Following\n\tContinuously");
		}
	};

	float FollowBehaviour::Evaluate(Agent* agent) {
		// Retrieve a reference to the target agent
		Agent* target = agent->GetTarget();

		// Check the distance between our position and the target agent's current position
		float distance = glm::distance(agent->GetPosition(), target->GetPosition());

		// Set a maximum evaluation distance of 10 cells (score 0 when 10 or more cells away)
		float eval = 10 * AIForGames::sizeOfCell - distance;

		// Return a score between [0] and [10 * cell size], increasing the probability of following as the two agents get closer together
		if (eval < 0) {0;};
		return eval;
	};
}