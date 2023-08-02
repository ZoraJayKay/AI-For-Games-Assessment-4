#pragma once
#include "Behaviour.h"

namespace AIForGames {

	// A class for conditionally selecting a behaviour from those available
	class SelectorBehaviour : public Behaviour
	{
	private:
		// Pointers for handling behaviours
		Behaviour* m_b1;
		Behaviour* m_b2;
		Behaviour* m_currentBehaviour;

	public:
		SelectorBehaviour();
		SelectorBehaviour(Behaviour* b1, Behaviour* b2);
		~SelectorBehaviour();

		// This is a virtual void Update to override the pure virtual void Update in the base abstract class.
		virtual void Update(Agent* agent, float deltaTime);

		void SetBehaviour(Behaviour* bhv, Agent* agent);

		// Improvised function for when the destructor doesn't call because I'm using an Agent object rather than an Agent*
		virtual void DestroyPointers();
	};
}

