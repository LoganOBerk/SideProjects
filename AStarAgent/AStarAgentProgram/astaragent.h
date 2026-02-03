#pragma once
#include "agent.h"
class AStarAgent : public Agent {
private:
	//Calculates provided heuristic formula based on board configuration
	int heuristic(State& s);
public:
	AStarAgent(int[yAxis][xAxis], int[yAxis][xAxis]);
	void genChild(State*, std::string);
	void findShortestPath();
	void setInit(int[yAxis][xAxis]);
	void setGoal(int[yAxis][xAxis]);
};