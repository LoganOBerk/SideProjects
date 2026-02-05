#pragma once

#include "Agent.h"

//Specific Agent designed to strictly implement A* algorithm
//with custom path finding, class specific heuristic, initialization, and child generation
class AStarAgent : public Agent {
private:
	// Calculates provided heuristic formula based on board configuration
	int heuristic(State& s);

public:
	AStarAgent(int[yAxis][xAxis], int[yAxis][xAxis]);

	void genChild(State*, const std::string);
	void findShortestPath();
	void setInit(int[yAxis][xAxis]);
	void setGoal(int[yAxis][xAxis]);
};
