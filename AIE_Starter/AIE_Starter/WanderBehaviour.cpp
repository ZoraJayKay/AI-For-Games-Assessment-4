#include "WanderBehaviour.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "Agent.h"

namespace AIForGames {
	WanderBehaviour::WanderBehaviour() {};
	WanderBehaviour::~WanderBehaviour() {};

	// An Update function to set an Agent and its PathAgent wandering the map randomly
	void WanderBehaviour::Update(Agent* agent, float deltaTime) {
		// If the Agent's PathAgent has navigated to the end of its path, pick another random node and go there.
		if (agent->PathComplete()) {
			// If this agent is NOT being run by the UtilityAI then print this (the UtilityAI has its own printout)
			if (agent->GetType() == Agent::UtilityAI) {
				agent->SetStateText("UAI Wandering\n\t3 sec behaviour refresh");
			}

			else if (agent->GetType() == Agent::FiniteStateMachine) {
				agent->SetStateText("FSM Wandering\n\tContinuous behaviour refresh");
			}

			else {
				agent->SetStateText("Wandering\n\tAlways");
			}

			// Record a random node in the NodeMap
			Node* randomNode = agent->GetMap()->GetRandomNode();
			// Instruct the agent to move to the coordinates of the random node
			agent->GoTo(glm::vec2(randomNode->position.x, randomNode->position.y));
		}
	};

	float WanderBehaviour::Evaluate(Agent* agent) {
		// Retrieve a reference to the target agent
		Agent* target = agent->GetTarget();

		// Check the distance between our position and the target agent's current position
		float distance = glm::distance(agent->GetPosition(), target->GetPosition());
		
		float eval = distance;

		// Return a score between [0] and [the two most distant points of the map], increasing the probability of wandering as the two agents get further away from one another
		if (eval < 0) { 0; };
		return eval;
	};
}