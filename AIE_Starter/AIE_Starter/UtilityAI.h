#pragma once
#include "Behaviour.h"
#include <vector>

namespace AIForGames {
	class WanderBehaviour;
	class FollowBehaviour;

	// A root Behaviour for an Agent which selects Behaviours subject to their suitability for the situation
	class UtilityAI : public Behaviour
	{
	private:
		// A collection of pointers to all possible Behaviours
		std::vector<Behaviour*> m_behaviours;

		// A reference pointer to the current Behaviour
		Behaviour* currentBehaviour;


	public:
		UtilityAI();
		UtilityAI(Behaviour* defaultBehaviour);

		~UtilityAI();

		// This pure virtual function is a null pointer to a function (=0) so it cannot implement a new Update within the Behaviour class. Derived classes (other Behaviours) can override this function, and we can create instances of them because they make the function a non-null pointer.
		virtual void Update(Agent* agent, float deltaTime);

		// Improvised function for when the destructor doesn't call because I'm using an Agent object rather than an Agent* - ONLY USED FOR SelectorBehaviour
		virtual void DestroyPointers();

		//// A function for when the Behaviour becomes active (not PURE virtual because not all Behaviours require specific functionality here)
		//virtual void Enter(Agent* agent);

		//// A function for when the Behaviour ceases being active (not PURE virtual because not all Behaviours require specific functionality here)
		//virtual void Exit(Agent* agent);

		//// A function used by UtilityAI to calculate a numerical priority / suitability score for a given Behaviour that calls this function (0 by default)
		//virtual float Evaluate(Agent* agent);

		// A function for adding to the collection of Behaviours of this UtilityAI
		void AddBehaviour(Behaviour* behaviour);
	};
}