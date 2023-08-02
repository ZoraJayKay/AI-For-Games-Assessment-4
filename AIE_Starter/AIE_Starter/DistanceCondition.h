#pragma once
#include "Condition.h"


namespace AIForGames {

	// A Condition for choosing a Transition to a particular State based on the distance between Agents
	class DistanceCondition : public Condition
	{
	private:
		float m_distance;
		bool m_lessThan;

	public:
		DistanceCondition();
		DistanceCondition(float distance, bool lessThan);
		~DistanceCondition();

		float GetDistance();
		
		// A pure virtual boolean test to determine game-specific logic for Transitions that are derived from a Condition
		virtual bool IsTrue(Agent* agent);
	};
}

