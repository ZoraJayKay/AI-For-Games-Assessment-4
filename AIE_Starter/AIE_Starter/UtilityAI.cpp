#include "UtilityAI.h"
#include "Agent.h"
#include <string>
#include <typeinfo>
#include <iostream>


namespace AIForGames {
	UtilityAI::UtilityAI() {
		currentBehaviour = nullptr;
	};

	UtilityAI::UtilityAI(Behaviour* defaultBehaviour) {
		currentBehaviour = nullptr; 
		AddBehaviour(defaultBehaviour);
	};

	UtilityAI::~UtilityAI(){
		for (Behaviour* b : m_behaviours) {
			delete b;
			b = nullptr;
		}
	}

	void UtilityAI::Update(Agent* agent, float deltaTime) {
		if (currentBehaviour == nullptr) {
			currentBehaviour = m_behaviours[0];
		}

		// When the shot timer * delta time = 3 (approximately three seconds) update decision making
		if (agent->GetTimeInBehaviour() * deltaTime >= 3) {
			std::cout << "3 seconds has passed, update behaviour" << std::endl;

			// The presumed baseline is nil
			float bestEval = 0;

			// Reference pointer for selecting the highest evaluated Behaviour to apply 
			Behaviour* newBehaviour = nullptr;

			// Evaluate all Behaviours and select the one that is the most suitable (has the highest score)
			for (Behaviour* b : m_behaviours) {
				float eval = b->Evaluate(agent);
				if (eval > bestEval) {
					bestEval = eval;
					newBehaviour = b;
				}
			}

			// If the highest non-nil Behaviour differs from the current one...
			if (newBehaviour != nullptr && newBehaviour != currentBehaviour) {
				// and so long as the current Behaviour isn't null...
				if (currentBehaviour) {
					// Exit the current Behaviour, switch the two, and enter the new Behaviour
					currentBehaviour->Exit(agent);
					currentBehaviour = newBehaviour;
					currentBehaviour->Enter(agent);
				}
			}			

			// Reset the counter
			agent->SetTimeInBehaviour(0);
			// Update the agent with the highest-scored Behaviour in place
			currentBehaviour->Update(agent, deltaTime);
		}

		else {
			// Advance the behaviour recalc timer
			float newTime = agent->GetTimeInBehaviour() + 1;
			// Apply the updated timer to the agent
			agent->SetTimeInBehaviour(newTime);
			// Continue with whatever the behaviour is
			currentBehaviour->Update(agent, deltaTime);
		}
	};


	// Improvised function for when the destructor doesn't call because I'm using an Agent object rather than an Agent* - ONLY USED FOR SelectorBehaviour
	void UtilityAI::DestroyPointers() {};

	// A function for adding to the collection of Behaviours of this UtilityAI
	void UtilityAI::AddBehaviour(Behaviour* behaviour) {
		m_behaviours.push_back(behaviour);
	};
}