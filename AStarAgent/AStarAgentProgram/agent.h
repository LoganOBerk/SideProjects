#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include "globals.h"
#include "state.h"

#pragma once
//Agent wrapper class used for high level state handling and solution finding given init and goal 
class Agent {
private:
	State init;
	State goal;

	//Storage for search space
	std::priority_queue<State*, std::vector<State*>, State::Comparator> frontier; //next states to explore
	std::unordered_map<State, int, State::StateHash> exploredSet; //states already explored

	std::stack<State*> solutionSet; //final storage for solution set, for ease of printing since stack is LIFO

	//Storage vector to keep track of all memory on heap
	std::vector<State*> allocatedMem;

	//Index used to keep track of when a state was inserted for tie breaks
	int insertionIndex;
	int locX(int val, State& s);
	int locY(int val, State& s);
	//tilesOutOfPlace helper function used inside heuristic to find all tiles currently not in correct spot
	int tilesOutOfPlace(const State& curr, const State& goal);

	//Calculates provided heuristic formula based on board configuration
	int heuristic(State& s);
public:
	//Agent constructor, and destructor
	Agent(int[yAxis][xAxis], int[yAxis][xAxis]);
	~Agent();

	//Searching Algorithm
	void findShortestPath();
	//Child generation function handles which child to generate and when to skip
	void genChild(State*, std::string);
	void populateSolnSet(State*, bool);
	//Setters for Agent constructor parameters allowing setting of various inital and goal states
	void setInit(int[yAxis][xAxis]);
	void setGoal(int[yAxis][xAxis]);

	//Printer for solution set, essentially popping off the stack one by one
	void printSolutionSet();
};