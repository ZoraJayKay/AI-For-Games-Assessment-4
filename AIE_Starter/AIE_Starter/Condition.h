#pragma once

// The Condition is an abstract class with a virtual boolean test. We derive from the Condition to provide game-specific logic to drive our state Transitions

namespace AIForGames {
	class Agent;

	class Condition {
	public:
		Condition();
		~Condition();

		// A pure virtual boolean test to determine game-specific logic for Transitions that are derived from a Condition
		virtual bool IsTrue(Agent* agent) = 0;
	};
}