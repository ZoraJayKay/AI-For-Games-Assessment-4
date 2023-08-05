#include "PathAgent.h"
#include "NodeMap.h"
#include <cmath>
#include <iostream>

namespace AIForGames {
	PathAgent::PathAgent() {};
	PathAgent::~PathAgent() {};

	std::vector<Node*> PathAgent::GetPath() {
		return m_path;
	}

	// A function for setting the physical location of the PathAgent
	void PathAgent::SetNode(Node* node) {
		m_currentNode = node;
		m_position.x = node->position.x;
		m_position.y = node->position.y;
	};

	void PathAgent::SetSpeed(float spd) {
		m_speed = spd;
	};

	float PathAgent::GetSpeed() {
		return m_speed;
	}

	float PathAgent::GetSpeedModifier() {
		return m_speedModifier;
	}

	void PathAgent::SetSpeedModifier(float mod) {
		m_speedModifier = mod;
	}

	void PathAgent::Update(float deltaTime) {
		// 1: If the path is empty, Don't go anywhere, and empty the path so future updates do nothing.
		if (m_path.empty()) {
			return;
		}
		
		// 2: If the closest node is a null pointer, or it is the last node in the path, don't update the current node, otherwise do
		if (GetMap()->GetClosestNode(GetAgentPosition()) != nullptr && 
			GetMap()->GetClosestNode(GetAgentPosition()) != m_path.back()) {
				SetAgentCurrentNode(GetMap()->GetClosestNode(GetAgentPosition()));
		}

		// 3: Calculate a vector from the position of the next node to our current position (actual position, not node position)
		int xDistance = 0;
		int yDistance = 0;
		
		// 3.a.i: If we're only moving one node and this path has never been updated before (it has never had a chance to hit the path-end condition further below) then only calculate based on itself
		if (m_path.front() == m_path.back()) {
			xDistance = m_path.back()->position.x - m_position.x;
			yDistance = m_path.back()->position.y - m_position.y;
		}

		// 3.b.i: Otherwise calculate on the basis of many nodes
		else {
			xDistance = m_path[m_currentIndex + 1]->position.x - m_position.x;
			yDistance = m_path[m_currentIndex + 1]->position.y - m_position.y;
		}

		glm::vec2 directionVector = {xDistance, yDistance};
		
		// 3.c: Calculate the distance (the vector's magnitude [square root of its coordinates squared])
		int distance = sqrt(
			(directionVector.x * directionVector.x) +
			(directionVector.y * directionVector.y));

		// 3.d: UNIT VECTOR TO NEXT NODE
		// 3.d.i: Calculate a unit vector by dividing the vector with its own magnitude
		glm::vec2 unitVector;
		unitVector.x = directionVector.x / distance;
		unitVector.y = directionVector.y / distance;

		// Set a base movement modifier of 100% (not modifying current speed)
		float moveDifficulty = 1;

		// 3.d.ii: In order to calculate the speed reduction owing to the cost of the Edge, find the Edge we're going to travel
		for (int i = 0; i < m_path[m_currentIndex]->connections.size(); i++) {
			if (m_path[m_currentIndex]->connections[i].targetNode == m_path[m_currentIndex + 1]) {
				moveDifficulty = m_path[m_currentIndex]->connections[i].cost;
				break;
			}
		}		

		// 3.d.iii: Set the cost of the Edge we're travelling as the difficulty to be applied to movement speed
		SetSpeedModifier(moveDifficulty);

		// 3.d.iv: Subtract speed * deltaTime from the distance (how much we're going to move this frame)
		int frameMoveTick = distance - ((GetSpeed() / GetSpeedModifier()) *deltaTime);

		// 3.d.v: If distance is greater than zero, then this frame we're just moving towards the target node; add speed * deltaTime * unit vector to our position
		if (frameMoveTick > 0) {
			m_position.x += ((GetSpeed() / GetSpeedModifier()) * deltaTime * unitVector.x);
			m_position.y += ((GetSpeed() / GetSpeedModifier()) * deltaTime * unitVector.y);
		}
		
		else {
			// 4: Otherwise, we've overshot the node.
			// 4.a.i: Add one to currentIndex.
			m_currentIndex += 1;

			std::vector<Node*>::iterator itr = find(m_path.begin(), m_path.end(), m_path[m_currentIndex]);
#ifndef NDEBUG
			std::cout << "Passed node " << m_currentIndex << std::endl;
#endif

			// 4.a.ii: If we've reached the end of our path...
			if (*itr == m_path.back()) {
#ifndef NDEBUG
				std::cout << "Path end reached." << std::endl;
#endif
				// Snap to the final node...
				SetNode(m_path.back());
				// ... and empty the path so future updates do nothing.
				m_path.clear();
				return;
			};

			// 4.a.iii: If we have a next node...
			if (itr != m_path.end()) {
#ifndef NDEBUG
				std::cout << "Path end not yet reached, continuing." << std::endl;
#endif
				// Then distance with the subtracted speed * deltaTime tells us how far we've overshot the node if we invert it.
				int overshoot = (distance - ((GetSpeed() / GetSpeedModifier()) * deltaTime));

				xDistance = m_path[m_currentIndex + 1]->position.x - m_position.x;
				yDistance = m_path[m_currentIndex + 1]->position.y - m_position.y;

				// Refresh vector
				directionVector = { xDistance, yDistance };

				// Refresh magnitude / distance
				distance = sqrt(
					(directionVector.x * directionVector.x) +
					(directionVector.y * directionVector.y));

				// Refresh unit vector 
				unitVector.x = directionVector.x / distance;
				unitVector.y = directionVector.y / distance;

				// ... and move along this vector by the overshoot distance from the previous next node.
				m_position.x += overshoot * unitVector.x;
				m_position.y += overshoot * unitVector.y;
			};
		}		
	};

	void PathAgent::GoToNode(Node* node) {
		// Call the pathfinding function to make and store a path from the current node to the given destination
		m_path = NodeMap::AStarSearch(m_currentNode, node);

		if (!m_path.empty()) {
			// Speed adjustment has not been implemented for path smoothing as I have not implemented a way to calculate the speed impact of Edge costs, as path smoothing does not use existing Edges.
			float speedMod = GetSpeedModifier();
			m_path = nodeMap->SmoothPath(m_path, speedMod);
			//this->SetSpeedModifier(speedMod);
		}

		// When we recalculate the path our next node is always the first one along the path, so we reset currentIndex to 0.
		m_currentIndex = 0;
	};

	void PathAgent::Draw() {
		DrawCircle((int)m_position.x, (int)m_position.y, 8, m_agentColour);
		
		// Draw the current behaviour of this agent below its circular shape
		DrawText(stateText, (int)m_position.x + 5, (int)m_position.y + 10, 4, m_agentColour);
	};

	void PathAgent::DrawWithRange() {
		DrawCircle((int)m_position.x, (int)m_position.y, 8, m_agentColour);

		DrawCircleLines((int)m_position.x, (int)m_position.y, AIForGames::sizeOfCell * 5, m_agentColour);

		// Draw the current behaviour of this agent below its circular shape
		DrawText(stateText, (int)m_position.x + 5, (int)m_position.y + 10, 4, m_agentColour);
	}

	void PathAgent::SetAgentCurrentNode(Node* node) {
		m_currentNode = node;
	}

	glm::vec2 PathAgent::GetAgentPosition() {
		return m_position;
	}

	void PathAgent::SetAgentPosition(glm::vec2 pos) {
		m_position.x = pos.x;
		m_position.y = pos.y;
	};

	// A function to reset the currentpath
	void PathAgent::Reset() {
		m_path.clear();
	}

	void PathAgent::SetColour(Color colour) {
		m_agentColour = colour;
	}

	void PathAgent::SetStateText(const char* text) {
		stateText = text;
	}

	Color PathAgent::GetColour() {
		return m_agentColour;
	}

	void PathAgent::SetMap(NodeMap* newMap) {
		nodeMap = newMap;
	}

	NodeMap* PathAgent::GetMap() {
		return nodeMap;
	};
}