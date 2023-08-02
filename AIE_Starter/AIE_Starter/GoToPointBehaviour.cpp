#include "GoToPointBehaviour.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "Agent.h"

namespace AIForGames {
	GoToPointBehaviour::GoToPointBehaviour() {};
	GoToPointBehaviour::~GoToPointBehaviour() {};

	// An Update function that reads the mouse and sets the PathAgent moving
	void GoToPointBehaviour::Update(Agent* agent, float deltaTime) {
		if (IsMouseButtonPressed(0)) {
			Vector2 mousePos = GetMousePosition();
			agent->GoTo(glm::vec2(mousePos.x, mousePos.y));			
		}
	};
}