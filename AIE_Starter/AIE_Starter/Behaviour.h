#pragma once

namespace AIForGames {
	// Forward declaration of the Agent class to avoid cyclic dependency beginning with Agent needing to #include "Behaviour.h". We don't know WHAT the Agent Behaviour will be, just that there will be one. In contrast, note that we need to include PathAgent.h in Agent.h because we have a whole PathAgent embedded in our Agent, not just a pointer. The compiler needs to know how big a PathAgent is, and how many bytes to allocate for it there.
	class Agent;

	// Abstract class with pure virtual update function
	class Behaviour
	{
	public:
		// This pure virtual function is a null pointer to a function (=0) so it cannot implement a new Update within the Behaviour class. Derived classes (other Behaviours) can override this function, and we can create instances of them because they make the function a non-null pointer.
		virtual void Update(Agent* agent, float deltaTime) = 0;

		// Improvised function for when the destructor doesn't call because I'm using an Agent object rather than an Agent* - ONLY USED FOR SelectorBehaviour
		virtual void DestroyPointers() = 0;

		// A function for when the Behaviour becomes active (not PURE virtual because not all Behaviours require specific functionality here)
		virtual void Enter(Agent* agent) {};

		// A function for when the Behaviour ceases being active (not PURE virtual because not all Behaviours require specific functionality here)
		virtual void Exit(Agent* agent) {};

		// A function used by UtilityAI to calculate a numerical 'priority 'suitability' score for a given Behaviour that calls this function (0 by default)
		virtual float Evaluate(Agent* agent) { return 0.0f; };
	};
}