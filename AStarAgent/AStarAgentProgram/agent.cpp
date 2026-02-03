#include "agent.h"

//Function used for locating x coordinate in cartesian representation (1 based indexing)
int Agent::locX(int val, State& s) {
	return s.tileX[val];
}


//Function used for locating y coordinate in cartesian representation (1 based indexing)
int Agent::locY(int val, State& s) {
	return s.tileY[val];
}




Agent::~Agent() {
	for (State* alloc : allocatedMem) {
		delete alloc;
	}
}



int Agent::tilesOutOfPlace(const State& curr, const State& goal) {
	int outOfPlace = 0;
	for (int t = 1; t < nTiles; t++) {
		if (curr.tileX[t] != goal.tileX[t] || curr.tileY[t] != goal.tileY[t]) {
			outOfPlace++;
		}
	}
	return outOfPlace;
}












void Agent::populateSolnSet(State* s){
	//Once we hit our goal we want to push the solution path into the solutionSet
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
	//Pop our solution set off the stack
	while (!solutionSet.empty()) {
		solutionSet.top()->printState();
		solutionSet.pop();
	}
}
