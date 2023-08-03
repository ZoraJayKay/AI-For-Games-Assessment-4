#pragma once
#include <glm/glm.hpp>
//#include <vector>
#include "Pathfinding.h"
#include "raylib.h"

namespace AIForGames {
	class PathAgent
	{
	private:
		glm::vec2 m_position;
		std::vector<Node*> m_path;
		int m_currentIndex;
		Node* m_currentNode;
		float m_speed;
		Color m_agentColour;
		const char* stateText;

	public:
		PathAgent();
		~PathAgent();
		
		std::vector<Node*> GetPath();
		void SetNode(Node* node);
		void SetSpeed(int spd);
		void Update(float deltaTime);
		void GoToNode(Node* node);
		/*void Draw(Color colour);*/
		void Draw();
		void DrawWithRange();
		glm::vec2 GetAgentPosition();
		void SetAgentPosition(glm::vec2 pos);
		void SetAgentCurrentNode(Node* node);
		void Reset();
		void SetColour(Color colour);
		void SetStateText(const char* text);
		Color GetColour();
	};
}