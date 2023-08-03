/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "Pathfinding.h"
#include <string>;
#include "memory.h"
#include "NodeMap.h"
#include <iostream>
#include "Agent.h"
#include "PathAgent.h"
#include "GoToPointBehaviour.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "SelectorBehaviour.h"
#include "DistanceCondition.h"
#include "State.h"
#include "FiniteStateMachine.h"
#include "UtilityAI.h"

using namespace std;
using namespace AIForGames;

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1500;
	int screenHeight = 900;

	InitWindow(screenWidth, screenHeight, "Zora Jane Kerr: Artificial Intelligence for Games (Assessment 4 - Design and Implement One Other A.I. Strategy for a Non-Player Character) AIE, 2023 (student year 1)");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// ZORA: Tutorial requests making an ASCII art map to visualise the node map
	// Create a vector of strings, with each string representing a row line of the map.
	// "We can use a code such as 0 = solid wall, 1 =  navigable space, and set up anything from a simple test shape to a complex maze for pathfinding to take place in"
	
	vector<string> asciiMap;

	// 25x17 grid of chars denoting whether or not a cell is navigable (1) or impassable (0) /// ALTERNATE MAP
	asciiMap.push_back("0000000000000000000000000");     // row 1
	asciiMap.push_back("0101110111000011100111100");     // row 2
	asciiMap.push_back("0101011101111110111100110");     // row 3
	asciiMap.push_back("0101000000001010011000010");     // row 4
	asciiMap.push_back("0101111111101111001011110");     // row 5
	asciiMap.push_back("0100000010001001111010000");     // row 6
	asciiMap.push_back("0111110000111001001011110");     // row 7
	asciiMap.push_back("0000011111100001000010010");     // row 8
	asciiMap.push_back("0111110100111111111011110");     // row 9
	asciiMap.push_back("0100011100100010111010100");     // row 10
	asciiMap.push_back("0100010100100010101010110");     // row 11
	asciiMap.push_back("0111110111111110111010100");     // row 12
	asciiMap.push_back("0010100010000010001011100");     // row 13
	asciiMap.push_back("0111111110111011111110110");     // row 14
	asciiMap.push_back("0100000000101001000000010");     // row 15
	asciiMap.push_back("0111111111111111111111110");     // row 16
	asciiMap.push_back("0000000000000000000000000");     // row 17

	// Create a NodeMap class with a width, height and cell size, ie the spacing in pixels between consecutive squares in the grid. We’ll give it a function to initialize its data from the ASCII map declared above.
	NodeMap* map = new NodeMap();
	map->Initialise(asciiMap, AIForGames::sizeOfCell);

	// Set the starting node for the A* search equal to the Node* in column index 1, row index 1 (in the ascii map)
	Node* start = map->GetNode(1, 1);

	// ******************************************
	// Set up a Finite State Machine, having two states each with their own condition for activation
	// Define a DistanceCondition which will be satisfied if two agents are closer than 5 cells
	DistanceCondition* closerThan5 = new DistanceCondition(5.0f * AIForGames::sizeOfCell, true);

	// Define a DistanceCondition which will be satisfied if two agents are further apart than 7 cells
	DistanceCondition* fartherThan7 = new DistanceCondition(7.0f * AIForGames::sizeOfCell, false);

	// Incorporate these states into the FSM
	// 1: Add Behaviours to the States
	State* wanderState = new State(new WanderBehaviour());
	State* followState = new State(new FollowBehaviour());
	// 2: Add Transitions to the States, including the Transition Condition for transitioning from one Behaviour to the other
	wanderState->AddTransition(closerThan5, followState);
	followState->AddTransition(fartherThan7, wanderState);

	// Create the FSM itself with a default position of wandering
	FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
	fsm->AddState(wanderState);
	fsm->AddState(followState);

	// ******************************************


	// ++++++++++++++++++++++++++++++++++++++++++
	// Set up a Utility AI and add two Behaviours to its collection

	UtilityAI* utilityAI = new UtilityAI(new WanderBehaviour);
	//utilityAI->AddBehaviour(new WanderBehaviour);
	utilityAI->AddBehaviour(new FollowBehaviour);

	// ++++++++++++++++++++++++++++++++++++++++++


	// Create a new player agent behaviour with the existing node map and the 'point and click' behaviour
	Agent player(map, new GoToPointBehaviour(), Agent::OnClick);
	player.SetStateText("Player");
	player.SetColour(YELLOW);
	player.SetSpeed(64);
	player.SetNode(start);
	
	// An agent for wandering the map randomly
	Agent agent_behaviour_01(map, new WanderBehaviour(), Agent::SingleBehaviour);
	agent_behaviour_01.SetColour(DARKGREEN);
	agent_behaviour_01.SetSpeed(64);
	agent_behaviour_01.SetNode(map->GetRandomNode());

	// An agent for following the player
	Agent agent_behaviour_02(map, new FollowBehaviour(), Agent::SingleBehaviour);
	agent_behaviour_02.SetColour(BLUE);
	agent_behaviour_02.SetSpeed(48);
	agent_behaviour_02.SetTarget(&player);
	agent_behaviour_02.SetNode(map->GetRandomNode());

	// An agent that switches its behaviour subject to proximity with the player
	Agent agent_03(map, new SelectorBehaviour(new FollowBehaviour(), new WanderBehaviour()), Agent::BehaviourSelector);
	agent_03.SetSpeed(32);
	agent_03.SetNode(map->GetRandomNode());
	agent_03.SetTarget(&player);

	// An agent whose behaviour is controlled by the FSM
	Agent agent_fsm(map, fsm, Agent::FiniteStateMachine);
	agent_fsm.SetNode(map->GetRandomNode());
	agent_fsm.SetColour(PURPLE);
	agent_fsm.SetSpeed(32);
	agent_fsm.SetTarget(&player);

	// An agent governed by a UtilityAI
	Agent agent_utility(map, utilityAI, Agent::UtilityAI);
	agent_utility.SetNode(map->GetRandomNode());
	agent_utility.SetColour(ORANGE);
	agent_utility.SetSpeed(48);
	agent_utility.SetTarget(&player);

	// Time at commencement of pathfinding
	float time = (float)GetTime();
	float deltaTime;

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Time at moment of update
		float fTime = (float)GetTime();

		// Change in time since last update
		deltaTime = fTime - time;

		// Reset timer for this update
		time = fTime;

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		// Draw the nodes of the map
		map->Draw();

		// Draw a line that shows the current path of the PathAgent inside the Agent that is passed in
		map->DrawPath(player.GetPath(), YELLOW);
		map->DrawPath(agent_behaviour_01.GetPath(), DARKGREEN);
		map->DrawPath(agent_behaviour_02.GetPath(), DARKBLUE);
		map->DrawPath(agent_03.GetPath(), agent_03.AgentColour());
		map->DrawPath(agent_fsm.GetPath(), agent_fsm.AgentColour());
		map->DrawPath(agent_utility.GetPath(), agent_utility.AgentColour());

		// Update the behaviour of the Agent that encapsulates the PathAgent
		player.Update(deltaTime);
		agent_behaviour_01.Update(deltaTime);
		agent_behaviour_02.Update(deltaTime);
		agent_03.Update(deltaTime);
		agent_fsm.Update(deltaTime);
		agent_utility.Update(deltaTime);

		// Draw the PathAgent inside of the Agent
		player.Draw();
		agent_behaviour_01.Draw();
		agent_behaviour_02.Draw();
		agent_03.Draw();
		agent_fsm.Draw();
		agent_utility.Draw();

		// Finish
		EndDrawing();

		//----------------------------------------------------------------------------------


		//if (IsMouseButtonPressed(0)) {
		//	Vector2 mousePos = GetMousePosition();
		//	Node* end = map->GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
		//	map->ClearMapVals();
		//	// On mouse click, set the agent's current node = the nearest node to its current world position
		//	agent.SetAgentCurrentNode(map->GetClosestNode(glm::vec2(agent.GetAgentPosition().x, agent.GetAgentPosition().y)));
		//	agent.GoToNode(end);
		//}


		//// ----- This code is just for demonstrating moving the path's origin -----
		//// If left mouse is clicked...
		//if (IsMouseButtonPressed(0)) {
		//	map->ClearMapVals();
		//	Vector2 mousePos = GetMousePosition();
		//	start = map->GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
		//	nodeMapPath = map->AStarSearch(start, end);
		//	nodeMapPath = NodeMap::AStarSearch(start, end);
		//}

		//// ----- This code is just for demonstrating moving the path's destination -----
		////// If right mouse is clicked...
		//if (IsMouseButtonPressed(1)) {
		//	map->ClearMapVals();
		//	Vector2 mousePos = GetMousePosition();
		//	end = map->GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
		//	nodeMapPath = map->AStarSearch(start, end);
		//	nodeMapPath = NodeMap::AStarSearch(start, end);
		//}

		
		//map->DrawPath(nodeMapPath);
		//map->DrawPath(agent.GetPath());

		/*agent.Update(deltaTime);
		agent.Draw();*/

		

		//EndDrawing();

		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	// To delete SelectorBehaviour's pointers (unclear why the destructor won't do this...?)
	agent_03.GetBehaviour()->DestroyPointers();

	delete fsm;
	fsm = nullptr;

	delete utilityAI;
	utilityAI = nullptr;

	delete map;
	map = nullptr;	

	return 0;
}