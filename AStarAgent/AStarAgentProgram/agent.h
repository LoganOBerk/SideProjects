#pragma once

#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

#include "Globals.h"
#include "State.h"

// Agent abstract class used for managing data such as what we have seen(explored set), where we are going(frontier),
// what memory has been allocated, and what is our solution set.
// Agent is also responsible for providing general functions that can be used across various agents if needed,
// and defining which functions will need to be defined per Agent
class Agent {
protected:
	// Initial and goal states
	State init;
	State goal;

	// Storage for search space
	std::priority_queue<State*, std::vector<State*>, State::Comparator> frontier; // next states to explore
	std::unordered_map<State, int, State::StateHash> exploredSet;                 // states already explored

	// Final storage for solution set, for ease of printing since stack is LIFO
	std::stack<State*> solutionSet;

	// Storage vector to keep track of all memory on heap
	std::vector<State*> allocatedMem;

	// Index used to keep track of when a state was inserted for tie breaks
	int insertionIndex = 0;

	const int locX(const int val, const State& s) const;
	const int locY(const int val, const State& s) const;

	// tilesOutOfPlace function used to find all tiles currently not in correct spot
	const int tilesOutOfPlace(const State& curr, const State& goal) const;
	void populateSolnSet(State*);

public:
	// Agent constructor and destructor
	Agent() {};
	~Agent();

	// Searching algorithm
	virtual void findShortestPath() = 0;

	// Child generation function handles which child to generate and when to skip
	virtual void genChild(State*, const std::string) = 0;

	// Setters for Agent constructor parameters allowing setting of various initial and goal states
	virtual void setInit(int[yAxis][xAxis]) = 0;
	virtual void setGoal(int[yAxis][xAxis]) = 0;

	// Printer for solution set, essentially popping off the stack one by one
	void printSolutionSet();
};
