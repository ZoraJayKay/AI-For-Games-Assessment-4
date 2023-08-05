#pragma once
#include <glm/glm.hpp>
#include "Behaviour.h"

namespace AIForGames {

	class SteeringForce;

	class SteeringBehaviour : public Behaviour
	{
	private:
		// A reference pointer for the current 
		SteeringForce* currentForce;

	public:
		SteeringBehaviour();
		~SteeringBehaviour();

		SteeringForce* GetCurrentForce();

		virtual void Update(Agent* agent, float deltaTime);
	};
}