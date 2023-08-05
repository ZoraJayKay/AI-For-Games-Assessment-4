#pragma once
#include <glm/glm.hpp>

namespace AIForGames {
	class Agent;

	class SteeringForce
	{
	public:
		SteeringForce();
		~SteeringForce();
		virtual glm::vec2 GetForce(Agent* agent) = 0;

	private:


	};
}