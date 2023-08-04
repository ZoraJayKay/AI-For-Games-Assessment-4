#pragma once
#include "Pathfinding.h"
#include <string>
#include "raylib.h"


// Use the same namespace as the one set up by the tutorial
namespace AIForGames {
	static int sizeOfCell = 40;

	// Create a new class within the namespace to hold the map of nodes
	class NodeMap
	{
		// Map variables
		int m_width;
		int m_height;

		// The size of every separate 'cell' within the map
		float m_cellSize;

		// From the tute: "The Node** variable nodes is essentially a dynamically allocated one dimensional array of Node pointers."
		Node** m_nodes;

	public:
		// Default constructor
		NodeMap();

		// Destructor
		~NodeMap();

		void GetMapSize();

		// A function to set the start/end position of the node map depending on which mouse button is pressed
		Node* GetClosestNode(glm::vec2 worldPos);

		// A function for the purposes of setting up a node map according to a vector of strings, called 'asciiMap', and a given size for each node to be
		// From the tute: "In the Initialise function we will allocate this array to match the width and height of the map (determined by the vector of strings passed in) and fill it with either newly allocated Nodes or null pointers for each square on the grid."
		void Initialise(std::vector<std::string> asciiMap, int cellSize);

		// A function to return the Node* for a given pair of coordinates
		Node* GetNode(int x, int y);

		// A function for drawing the best path calculated by a Dijkstra search
		void DrawPath(std::vector<Node*> path, Color colour);

		// A function to draw the map to the screen
		void Draw();

		// This is a global namespace function for the AIForGames namespace which will print the node path from back to front for a completed A* search.
		void Print(std::vector<Node*> path);

		// A function to set all pathfinding values to nil imbetween paths, so that only the nodes checked in the most recent path are shown on debugging
		void ClearMapVals();

		// A function to calculate the straight-line distance between one node and the end node
		static int Heuristic(Node* a, Node* b);

		// This is a function for calculating a series of Node Pointers that go from a start node to an end node.
		static std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);

		// A function for randomly selecting a node from the node map
		Node* GetRandomNode();

		// A function for returning whether it is true that there are no null pointer tiles between two points
		bool IsVisibleFrom(Node* start, Node* end);

		// A function for return a path of only two nodes if there is a clear line of sight between them
		std::vector<Node*> SmoothPath(std::vector<Node*> path, float& speedMod);
	};
}