#include "FiniteStateMachine.h"
#include "State.h"
#include "Condition.h"
#include "Agent.h"

namespace AIForGames {
	FiniteStateMachine::FiniteStateMachine() {};

	FiniteStateMachine::FiniteStateMachine(State* defaultState) {
		m_newState = nullptr;
		m_currentState = defaultState;
	};
	
	FiniteStateMachine::~FiniteStateMachine() {
		// Delete all of the States belonging to the FSM
		for (State* state : m_states) {
			delete state;
			state = nullptr;
		}
	};

	void FiniteStateMachine::Update(Agent* agent, float deltaTime) {
		// When the time spent in this behaviour is more than * delta time = 1 (approximately one second) update state decision making
		if (agent->GetTimeInBehaviour() * deltaTime >= 1) {
			// Check all transitions and see if we have a new state that we want to transition to
			// The new state
			m_newState = nullptr;

			// Check all of the Transitions of the the current State
			for (State::Transition transition : m_currentState->GetTransitions()) {
				// If the Transition condition is satisfied...
				if (transition.condition->IsTrue(agent)) {
					// Then transition to the target State of that Transition
					m_newState = transition.targetState;
				}
			}

			// If we changed state (if newState got set as anything at all)
			if (m_newState != nullptr) {
				// 1: Exit the current State
				m_currentState->Exit(agent);

				// 2: Change current State
				m_currentState = m_newState;

				// 3: Enter the new State
				m_currentState->Enter(agent);
			}

			// Reset the counter
			agent->SetTimeInBehaviour(0);
		}

		else {
			// Advance the behaviour recalc timer
			float newTime = agent->GetTimeInBehaviour() + 1;
			// Apply the updated timer to the agent
			agent->SetTimeInBehaviour(newTime);
		}

		m_currentState->Update(agent, deltaTime);
	}

	// A function for adding possible States to the FSM
	void FiniteStateMachine::AddState(State * state) {
		m_states.push_back(state);
	};

	// Improvised function for when the destructor doesn't call because I'm using an Agent object rather than an Agent*
	void FiniteStateMachine::DestroyPointers() {
		// Delete all of the States belonging to the FSM
		for (State* state : m_states) {
			delete state;
			state = nullptr;
		}
	};

	void FiniteStateMachine::Enter(Agent* agent) {
		m_currentState->Enter(agent);
	};
}