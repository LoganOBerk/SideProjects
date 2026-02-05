#include "Agent.h"

// Function used for locating x coordinate in cartesian representation (1 based indexing)
const int Agent::locX(const int val, const State& s) const{
	return s.tileX[val];
}

// Function used for locating y coordinate in cartesian representation (1 based indexing)
const int Agent::locY(const int val, const State& s) const{
	return s.tileY[val];
}

Agent::~Agent() {
	for (State* alloc : allocatedMem) {
		delete alloc;
	}
}

const int Agent::tilesOutOfPlace(const State& curr, const State& goal) const{
	int outOfPlace = 0;
	for (int t = 1; t < nTiles; t++) {
		if (curr.tileX[t] != goal.tileX[t] || curr.tileY[t] != goal.tileY[t]) {
			outOfPlace++;
		}
	}
	return outOfPlace;
}

void Agent::populateSolnSet(State* s) {
	// Once we hit our goal we want to push the solution path into the solutionSet
	while (s != nullptr) {
		solutionSet.push(s);
		s = s->p;
	}
}

void Agent::printSolutionSet(){
	if (solutionSet.empty()) {
		std::cout << "No solution possible!" << std::endl;
		std::cout << "Configurations Tried: " << exploredSet.size() << std::endl;
	}

	// Pop our solution set off the stack
	while (!solutionSet.empty()) {
		solutionSet.top()->printState();
		solutionSet.pop();
	}
}
