#include "astaragent.h"

AStarAgent::AStarAgent(int initConfig[yAxis][xAxis], int goalConfig[yAxis][xAxis]) {
	setGoal(goalConfig);
	setInit(initConfig);
}

void AStarAgent::findShortestPath() {
	State* n = &init; //Point to the initial State
	int expansionOrder = 1;

	while (true) {
		//Increment after each State is expanded from and update its order
		n->expO = expansionOrder++;

		//If we reach the goal reassign our goal so its pointing to correct parents and exit
		if (*n == goal) {
			goal = *n; //Mainly to keep solution path continuity within Agent not strictly necessary
			break;
		}

		//Generate child based on empty spaces possible moves
		if (n->eX > 1) genChild(n, "LEFT");
		if (n->eX < xAxis) genChild(n, "RIGHT");
		if (n->eY > 1) genChild(n, "UP");
		if (n->eY < yAxis) genChild(n, "DOWN");

		//If no solution exists the frontier will be completely exhausted, so we exit
		if (frontier.empty()) {
			return;
		}
		//Reassign our pointer to the item at the front of the frontier
		n = frontier.top();
		//Remove from frontier
		frontier.pop();
		//Update explored set
		exploredSet[*n] = n->g;
	}
	populateSolnSet(n);

}
void AStarAgent::genChild(State* p, std::string d) {
	//make a pointer that is a copy of the passed in parent
	State* n = new State(*p);


	int dx = 0; //horizontal direction offset
	int dy = 0; //vertical direction offset
	int w = 0; //wind cost


	//Direction handlers updating internal state of the copied pointer to represent new child
	if (d == "LEFT") {
		dx = LEFT;
		w = WITHWIND;
	}
	if (d == "RIGHT") {
		dx = RIGHT;
		w = AGAINSTWIND;
	}
	if (d == "UP") {
		dy = UP;
		w = SIDEWIND;
	}
	if (d == "DOWN") {
		dy = DOWN;
		w = SIDEWIND;
	}

	n->moveTile(dx, dy);
	n->updateState(p, w, heuristic(*n), insertionIndex++);

	//If the generated child is in the explored set and the path cost
	//for the current child, g(n), is greater than or equal to the old child 
	//delete it and skip it 
	if (exploredSet.count(*n) && n->g >= exploredSet[*n]) {
		delete n;
		return;
	}
	//Update the explored set, frontier, and keep track of memory allocated
	exploredSet[*n] = n->g;
	frontier.push(n);
	allocatedMem.push_back(n);
}
int AStarAgent::heuristic(State& s) {
	int totalManhattan = 0;
	int x = 0;
	int y = 0;
	for (int t = 1; t < nTiles; t++) {
		x = locX(t, goal) - locX(t, s); //calculate x param of manhattan before absolute value
		y = locY(t, goal) - locY(t, s); //calculate y param of manhattan before absolute value

		//Identify if the difference is negative, this gives an idea of direction
		if (x < 0) {
			x = abs(x);
			x *= WITHWIND;
		}
		else if (x > 0) {
			x *= AGAINSTWIND;
		}

		//Since vertical distance is the same cost UP or DOWN there is only one handler
		if (y != 0) {
			y = abs(y);
			y *= SIDEWIND;
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



