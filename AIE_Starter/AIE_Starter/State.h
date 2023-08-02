#pragma once
#include <vector>

// The State has a collection of Behaviours, and a collection of Transitions. An example state might be a follow state, which holds a FollowBehaviour, and Conditions for when to switch to other states. We will not need to inherit from this class, but will put our game-specific logic into the Behaviours it references.

namespace AIForGames {
	class Behaviour;
	class Condition;
	class Agent;

	class State {
	public:
		State();
		State(Behaviour* behaviour);

		~State();

		// Each State must have one or more Transitions (ways to activate / access / navigate to that State)
		struct Transition {
			// The trigger needed to satisfy before this Transition will start
			Condition* condition;

			// A pointer to the State that this Transition will activate
			State* targetState;
		};

		// This is a virtual void Update so the State's Behaviours can override the pure virtual void Update in the base abstract Behaviour class.
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Enter(Agent* agent);
		virtual void Exit(Agent* agent);
		std::vector<Transition> GetTransitions();
		void AddTransition(Condition* transitionCondition, State* state);

	private:
		// A vector of Behaviour pointers (the base, abstract class) so that the collection can polymorphically hold its various derived classes of specific behaviours. The State owns these behaviours.
		std::vector<Behaviour*> m_behaviours;

		// A vector of Transition pointers
		std::vector<Transition> m_transitions;

	};
}