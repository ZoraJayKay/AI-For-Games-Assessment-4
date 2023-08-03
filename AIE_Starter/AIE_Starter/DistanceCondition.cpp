#include "DistanceCondition.h"
#include <glm/glm.hpp>
#include "Agent.h"

namespace AIForGames {
	DistanceCondition::DistanceCondition() {};
	DistanceCondition::DistanceCondition(float distance, bool lessThan) : m_distance(distance), m_lessThan(lessThan) {};
	DistanceCondition::~DistanceCondition() {};

	float DistanceCondition::GetDistance() {
		return m_distance;
	};

	// A pure virtual boolean test to determine game-specific logic for Transitions that are derived from a Condition
	bool DistanceCondition::IsTrue(Agent* agent) {
		// if it is true that the distance between this agent and its target is less than the threshold distance, return true.
		return glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) <= m_distance == m_lessThan;
	};
}