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

		NodeMap* GetMap();
		float GetMaxVelocity();
		float GetVelocity();
		glm::vec2 GetMaxForce();
		Agent* GetTarget();
		std::vector<Node*> GetPath();
		PathAgent GetAgent();
		Behaviour* GetBehaviour();
		AgentControlType GetType();
		float GetTimeInBehaviour();
		const char* GetStateText();
		glm::vec2 GetPosition();

		void AddForce(glm::vec2 force);
		void SetNode(Node* node);
		void SetSpeed(int speed);
		void SetAgent(PathAgent agent);
		void SetTarget(Agent* target);
		void SetMaxVelocity(float maxVel);
		void SetVelocity(float vel);
		void SetMaxForce(glm::vec2 maxFrc);
		void SetColour(Color colour);
		void SetStateText(const char* text);
		Color AgentColour();
		void SetTimeInBehaviour(float time);

		bool PathComplete();		
		void Reset();

	private:
		PathAgent m_pathAgent;
		Behaviour* m_current;
		NodeMap* m_nodeMap;
		Color m_colour;
		Agent* m_targetAgent;
		const char* m_stateText;
		AgentControlType m_type;
		float timeInBehaviour;
		float MaxVelocity;
		glm::vec2 MaxForce;
		glm::vec2 Force;
		float Velocity;
	};
}