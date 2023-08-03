#pragma once
#include "NodeMap.h"
#include "PathAgent.h"
#include "raylib.h"
#include "Behaviour.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

namespace AIForGames {
	class NodeMap;

	class Agent
	{
	public:
		enum AgentControlType {
			OnClick,
			SingleBehaviour,
			BehaviourSelector,
			FiniteStateMachine,
			UtilityAI
		};

		Agent();
		Agent(NodeMap* _nodeMap, Behaviour* _behaviour);
		Agent(NodeMap* _nodeMap, Behaviour* _behaviour, AgentControlType type);
		~Agent();

		void Update(float deltaTime);
		void Draw();
		void GoTo(glm::vec2 point);
		void SetNode(Node* node);
		void SetSpeed(int speed);
		void SetAgent(PathAgent agent);
		std::vector<Node*> GetPath();
		bool PathComplete();
		NodeMap* GetMap();
		Agent* GetTarget();
		void SetTarget(Agent* target);
		glm::vec2 GetPosition();		
		void Reset();
		void SetColour(Color colour);
		void SetStateText(const char* text);
		const char* GetStateText();
		Color AgentColour();
		PathAgent GetAgent();
		Behaviour* GetBehaviour();		
		AgentControlType GetType();
		float GetTimeInBehaviour();
		void SetTimeInBehaviour(float time);
		

	private:
		PathAgent m_pathAgent;
		Behaviour* m_current;
		NodeMap* m_nodeMap;
		Color m_colour;
		Agent* m_targetAgent;
		const char* m_stateText;
		AgentControlType m_type;
		float timeInBehaviour;
	};
}