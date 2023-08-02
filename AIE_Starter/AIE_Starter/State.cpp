#include "State.h"
#include "Behaviour.h"
#include "Condition.h"

namespace AIForGames {
	State::State() {};

	State::State(Behaviour* behaviour) {
		m_behaviours.push_back(behaviour);
	};

	State::~State() {
		// Delete this state's Behaviour pointers
		for (Behaviour* behaviour : m_behaviours) {
			delete behaviour;
			behaviour = nullptr;
		}

		// Delete this State's Transition's Condition pointers
		for (Transition transition: m_transitions) {
			delete transition.condition;
			transition.condition = nullptr;
		}
	};

	// This is a virtual void Update so the State's Behaviours can override the pure virtual void Update in the base abstract Behaviour class.
	void State::Update(Agent* agent, float deltaTime) {
		// Update each Behaviour of the agent
		for (Behaviour* behaviour : m_behaviours) {
			behaviour->Update(agent, deltaTime);
		}
	}

	// A function for when the State becomes active (ask each Behaviour to call its own activation code)
	void State::Enter(Agent* agent) {};

	// A function for when the State ceases being active (ask each Behaviour to call its own activation cessation code)
	void State::Exit(Agent* agent) {

	};

	std::vector<State::Transition> State::GetTransitions() {
		return m_transitions;
	};

	void State::AddTransition(Condition* transitionCondition, State* state) {
		// Make a new Transition based on the passed-in information and set its member variables
		Transition t;
		t.condition = transitionCondition;
		t.targetState = state;
		// Add the new Transition to the lise for this State
		m_transitions.push_back(t);
	}
}