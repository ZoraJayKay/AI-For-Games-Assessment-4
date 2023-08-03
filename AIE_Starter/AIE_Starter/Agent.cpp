#include "Agent.h"

namespace AIForGames {
	Agent::Agent() {};

	Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_colour({ 255, 255, 0, 255 }) {
		_behaviour->Enter(this);
		timeInBehaviour = 0;
	};

	Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour, AgentControlType _type) : m_current(_behaviour), m_nodeMap(_nodeMap), m_colour({ 255, 255, 0, 255 }), m_type(_type) {
		_behaviour->Enter(this);
		timeInBehaviour = 0;
	};

	Agent::~Agent() {
		delete m_current;
		m_current = nullptr;
	};

	std::vector<Node*> Agent::GetPath() {
		return m_pathAgent.GetPath();
	}

	// This function updates the current Behaviour and then updates the PathAgent itself every frame
	void Agent::Update(float deltaTime) {
		if (m_current) {
			// Update the Behaviour of this Agent
			m_current->Update(this, deltaTime);
			// Update the PathAgent of this Agent
			m_pathAgent.Update(deltaTime);
		}
	};

	void Agent::Draw() {
		// For UtilityAI and FSM, draw the agent and its radius
		if (this->GetType() == UtilityAI || this->GetType() == FiniteStateMachine) {
			m_pathAgent.DrawWithRange();
		}
		
		// For all others, just draw the agent
		else {
			m_pathAgent.Draw();
		}
	};

	// A function that finds the nearest node to the given point and calculates a path to it.
	void Agent::GoTo(glm::vec2 point) {
		Node* end = m_nodeMap->GetClosestNode(point);
		m_nodeMap->ClearMapVals();
		// On mouse click, set the agent's current node = the nearest node to its current world position
		m_pathAgent.SetAgentCurrentNode(m_nodeMap->GetClosestNode(glm::vec2(m_pathAgent.GetAgentPosition().x, m_pathAgent.GetAgentPosition().y)));
		m_pathAgent.GoToNode(end);
	};

	// A function for setting the physical location of the PathAgent inside this Agent
	void Agent::SetNode(Node* node) {
		// Assign the parameter node passed in as the current node of the PathAgent inside this Agent
		m_pathAgent.SetAgentCurrentNode(node);
		// Assign the Cartesian coordinates of the node passed in as the coordinates of the PathAgent inside this Agent
		m_pathAgent.SetAgentPosition(glm::vec2(node->position.x, node->position.y));
	}

	void Agent::SetSpeed(int speed) {
		m_pathAgent.SetSpeed(speed);
	};

	void Agent::SetAgent(PathAgent agent) {
		m_pathAgent = agent;
	};

	// A function to return true if the PathAgent's path has been emptied (arrived at the node)
	bool Agent::PathComplete() {
		return m_pathAgent.GetPath().empty();
	};

	// A function to return the node map of this Agent's PathAgent
	NodeMap* Agent::GetMap() {
		return m_nodeMap;
	};

	Agent* Agent::GetTarget() {
		return m_targetAgent;
	}

	Behaviour* Agent::GetBehaviour() {
		return m_current;
	};

	PathAgent Agent::GetAgent() {
		return m_pathAgent;
	}

	void Agent::SetTarget(Agent* agent) {
		m_targetAgent = agent;
	}

	glm::vec2 Agent::GetPosition() {
		return m_pathAgent.GetAgentPosition();
	}

	// A function for resetting this agent's path
	void Agent::Reset() {
		m_pathAgent.Reset();
	};

	void Agent::SetColour(Color colour) {
		m_pathAgent.SetColour(colour);
	}

	void Agent::SetStateText(const char* text) {
		m_pathAgent.SetStateText(text);
	}

	const char* Agent::GetStateText() {
		return m_stateText;
	}

	Color Agent::AgentColour() {
		return m_pathAgent.GetColour();
	}

	Agent::AgentControlType Agent::GetType() {
		return m_type;
	}

	float Agent::GetTimeInBehaviour() {
		return timeInBehaviour;
	};

	void Agent::SetTimeInBehaviour(float time) {
		timeInBehaviour = time;
	};
}
