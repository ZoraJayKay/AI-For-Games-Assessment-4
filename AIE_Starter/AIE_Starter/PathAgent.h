#pragma once
#include <glm/glm.hpp>
#include "Pathfinding.h"
#include "raylib.h"

namespace AIForGames {
	class NodeMap;

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
		NodeMap* nodeMap;

	public:
		PathAgent();
		~PathAgent();
		
		void Draw();
		void DrawWithRange();
		Color GetColour();
		glm::vec2 GetAgentPosition();
		std::vector<Node*> GetPath();
		NodeMap* GetMap();
		void GoToNode(Node* node);
		void Reset();
		void SetMap(NodeMap* newMap);

		// A function for setting the physical location of the PathAgent
		void SetNode(Node* node);
		void SetSpeed(int spd);
		void SetAgentPosition(glm::vec2 pos);
		void SetAgentCurrentNode(Node* node);
		void SetColour(Color colour);
		void SetStateText(const char* text);
		void Update(float deltaTime);
	};
}