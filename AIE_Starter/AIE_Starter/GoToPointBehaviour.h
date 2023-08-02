#pragma once
#include "Behaviour.h"

namespace AIForGames {
	
	// A derived Behaviour class to activate on mouse click
	class GoToPointBehaviour : public Behaviour
	{
	public:
		GoToPointBehaviour();
		~GoToPointBehaviour();

		// This is a virtual void Update to override the pure virtual void Update in the base abstract class.
		virtual void Update(Agent* agent, float deltaTime);

		// Improvised function for when the destructor doesn't call because I'm using an Agent object rather than an Agent* - ONLY USED FOR SelectorBehaviour
		virtual void DestroyPointers() {};
	};
}