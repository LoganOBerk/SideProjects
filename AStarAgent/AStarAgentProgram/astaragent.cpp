#include "AStarAgent.h"

AStarAgent::AStarAgent(int initConfig[yAxis][xAxis], int goalConfig[yAxis][xAxis]) {
	setGoal(goalConfig);
	setInit(initConfig);
}

void AStarAgent::findShortestPath() {
	State* n = &init; // Point to the initial State
	int expansionOrder = 1;

	while (true) {
		// Increment after each State is expanded from and update its order
		n->expO = expansionOrder++;

		// If we reach the goal, reassign our goal so it's pointing to correct parents and exit
		if (*n == goal) {
			goal = *n; // Mainly to keep solution path continuity within Agent, not strictly necessary
			break;
		}

		// Generate child based on empty space's possible moves
		if (n->eX > 1) genChild(n, "WEST");
		if (n->eX < xAxis) genChild(n, "EAST");
		if (n->eY > 1) genChild(n, "NORTH");
		if (n->eY < yAxis) genChild(n, "SOUTH");

		// If no solution exists, the frontier will be completely exhausted, so we exit
		if (frontier.empty()) {
			return;
		}
		// Reassign our pointer to the item at the front of the frontier
		n = frontier.top();

		// Remove from frontier
		frontier.pop();

		// Update explored set
		exploredSet[*n] = n->g;
	}

	populateSolnSet(n);
}

void AStarAgent::genChild(State* p, const std::string d) {
	// Make a pointer that is a copy of the passed-in parent
	State* n = new State(*p);

	int dx = 0; // horizontal direction offset
	int dy = 0; // vertical direction offset
	int w = 0; // wind cost

	// Direction handlers for empty space movement, an empty space movement direction 
	// corresponds to the exact wind strength the adjacent tile is moving against
	// EXAMPLE: if an empty space moves north the adjacent tile is moving south against the northwind
	if (d == "WEST") {
		dx = WEST;
		w = WESTWIND;
	}
	if (d == "EAST") {
		dx = EAST;
		w = EASTWIND;
	}
	if (d == "NORTH") {
		dy = NORTH;
		w = NORTHWIND;
	}
	if (d == "SOUTH") {
		dy = SOUTH;
		w = SOUTHWIND;
	}

	n->moveEmptySpace(dx, dy);
	n->updateState(p, w, heuristic(*n), insertionIndex++);

	// If the generated child is in the explored set and the path cost
	// for the current child, g(n), is greater than or equal to the old child, delete it and skip it
	if (exploredSet.count(*n) && n->g >= exploredSet[*n]) {
		delete n;
		return;
	}

	// Update the explored set, frontier, and keep track of memory allocated
	exploredSet[*n] = n->g;
	frontier.push(n);
	allocatedMem.push_back(n);
}

int AStarAgent::heuristic(State& s) {
	int totalManhattan = 0;
	int x = 0;
	int y = 0;

	for (int t = 1; t < nTiles; t++) {
		x = locX(t, goal) - locX(t, s); // calculate x param of Manhattan before absolute value
		y = locY(t, goal) - locY(t, s); // calculate y param of Manhattan before absolute value

		//if a tile is moving WEST its moving against the eastwind, if its moving EAST its moving against the westwind
		if (x < 0) {
			x = abs(x);
			x *= EASTWIND;
		}
		else if (x > 0) {
			x *= WESTWIND;
		}

		//if a tile is moving SOUTH its moving against the northwind, if its moving NORTH its moving against the southwind
		if (y < 0) {
			y = abs(y);
			y *= NORTHWIND;
		}
		else if (y > 0) {
			y *= SOUTHWIND;
		}

		totalManhattan += (x + y);
	}

	return totalManhattan + tilesOutOfPlace(s, goal);
}

void AStarAgent::setInit(int initConfig[yAxis][xAxis]) {
	init = State(initConfig);
	init.h = heuristic(init);
}

void AStarAgent::setGoal(int goalConfig[yAxis][xAxis]) {
	goal = State(goalConfig);
}
