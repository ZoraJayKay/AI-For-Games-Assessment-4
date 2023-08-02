#pragma once
#include <vector>
#include "Behaviour.h"

// The FSM stores a lists of all possible States

namespace AIForGames {
	class State;
	class Agent;

	class FiniteStateMachine : public Behaviour {
	public:
		FiniteStateMachine();
		FiniteStateMachine(State* defaultState);

		~FiniteStateMachine();

		// A function for adding possible States to the FSM
		void AddState(State* state);

	private:
		// The collection of all possible States
		std::vector<State*> m_states;

		// The current State of the Finite State Machine
		State* m_currentState;

		// A pointer reference for transitioining States during the Update function
		State* m_newState;

		// This is a virtual void Update so the State's Behaviours can override the pure virtual void Update in the base abstract Behaviour class.
		virtual void Update(Agent* agent, float deltaTime);

		virtual void DestroyPointers();

		// Enter a given State
		void Enter(Agent* agent);
	};
}