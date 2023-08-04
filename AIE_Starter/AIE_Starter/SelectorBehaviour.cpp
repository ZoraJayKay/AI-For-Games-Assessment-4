#include "SelectorBehaviour.h"
#include "Agent.h"
#include <iostream>

namespace AIForGames {
	SelectorBehaviour::SelectorBehaviour() {};

	// Overloaded constructor wherein the passed-in parameters are set as the two Behaviour pointers
	SelectorBehaviour::SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2) {};

	// Destructor isn't triggering, presumably because I'm using SelectorBehaviour not as a pointer...?
	SelectorBehaviour::~SelectorBehaviour() {
		// b1 and b2 will have memory allocated to them in the main program so they need deleting before the program exits. m_currentBehaviour is a reference and not allocated memory at any point.
		delete m_b1;
		m_b1 = nullptr;

		delete m_b2;
		m_b2 = nullptr;

		std::cout << "Selector behaviour destructor completed." << std::endl;
	};

	// An Update function that conditionally toggles between behaviours based on state-dependent factors
	void SelectorBehaviour::Update(Agent* agent, float deltaTime) {
		// If the distance between the agent's target and itself is less than an arbitrary number of cells (5 here)
		if (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < (AIForGames::sizeOfCell * 5)) {
			// Change the agent's behaviour to the first saved option
			SetBehaviour(m_b1, agent);
			agent->SetStateText("Selector Found Player");
			agent->SetColour(RED);
			agent->SetSpeed(48);
		}

		else {
			// Change the agent's behaviour to the second saved option
			SetBehaviour(m_b2, agent);
			agent->SetStateText("Selector Wandering\n\tBehaviour refresh constant");
			agent->SetColour(GREEN);
			agent->SetSpeed(32);
		}

		// Update the newly-set existing behaviour
		m_currentBehaviour->Update(agent, deltaTime);
	};

	// Set the Agent's current behaviour to one passed in unless that is the current behaviour
	void SelectorBehaviour::SetBehaviour(Behaviour* bhv, Agent* agent) {
		if (m_currentBehaviour != bhv) {
			m_currentBehaviour = bhv;

			// Setting the agent's path to cleared will trigger its behavioural 'if empty, do x' check
			agent->Reset();
		}
	};

	// Improvised function for when the destructor doesn't call because I'm using an Agent object rather than an Agent*
	void SelectorBehaviour::DestroyPointers() {
		delete this->m_b1;
		this->m_b1 = nullptr;

		delete this->m_b2;
		this->m_b2 = nullptr;
	}
}