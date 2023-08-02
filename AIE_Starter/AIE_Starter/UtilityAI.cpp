#include "UtilityAI.h"
#include "Agent.h"
#include <string>
#include <typeinfo>


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

		WanderBehaviour* temp_01;
		FollowBehaviour* temp_02;

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

		int roundedScore = round(bestEval);
		std::string e = std::to_string(roundedScore);
		std::string f;

		// Not working yet
		// If the chosen Behaviour is to Wander...
		if (typeid(currentBehaviour) == typeid(temp_01)) {
			f = "Wandering\n\tWander utility score: " + e;
		}
		if (typeid(currentBehaviour) == typeid(temp_02)) {
			f = "Following\n\tFollow utility score: " + e;
		}		 

		const char* str = f.c_str();
		agent->SetStateText(str);
		
		// Update now with the highest-scored Behaviour in place
		currentBehaviour->Update(agent, deltaTime);
	};


	// Improvised function for when the destructor doesn't call because I'm using an Agent object rather than an Agent* - ONLY USED FOR SelectorBehaviour
	void UtilityAI::DestroyPointers() {};


	//// A function for when the Behaviour becomes active
	//void UtilityAI::Enter(Agent* agent) {};


	//// A function for when the Behaviour ceases being active
	//void UtilityAI::Exit(Agent* agent) {};


	//// A function used by UtilityAI to calculate a numerical 'priority 'suitability' score for a given Behaviour that calls this function (0 by default)
	//float UtilityAI::Evaluate(Agent* agent) { return 0; };

	// A function for adding to the collection of Behaviours of this UtilityAI
	void UtilityAI::AddBehaviour(Behaviour* behaviour) {
		m_behaviours.push_back(behaviour);
	};
}