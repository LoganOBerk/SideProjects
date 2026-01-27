#include "agent.h"

//Function used for locating x coordinate in cartesian representation (1 based indexing)
int Agent::locX(int val, State& s) {
	return s.tileX[val];
}


//Function used for locating y coordinate in cartesian representation (1 based indexing)
int Agent::locY(int val, State& s) {
	return s.tileY[val];
}

void Agent::setGoal(int goalConfig[yAxis][xAxis]) {
	goal = State(nullptr, 1, 0, 0, 0, goalConfig);
}



void Agent::setInit(int initConfig[yAxis][xAxis]) {
	init = State(nullptr, 1, 0, 0, 0, initConfig);
	init.h = heuristic(init);
}



Agent::Agent(int initConfig[yAxis][xAxis], int goalConfig[yAxis][xAxis]) {
	setGoal(goalConfig);
	setInit(initConfig);
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



int Agent::heuristic(State& s) {
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



void Agent::genChild(State* p, std::string d) {
	//make a pointer that is a copy of the passed in parent
	State* n = new State(*p);

	// reassign standard cartesian indexing to 0 based indexing
	int x = n->eX - 1;
	int y = n->eY - 1;


	int h = 0; //horizontal direction offset
	int v = 0; //vertical direction offset
	int w = 0; //wind cost


	//Assigning values we want to change
	int* oldVal = &n->config[y][x];
	int* oldX = &n->tileX[*oldVal];
	int* oldY = &n->tileY[*oldVal];


	//Direction handlers updating internal state of the copied pointer to represent new child
	if (d == "LEFT") {
		h = LEFT;
		w = WITHWIND;
	}
	if (d == "RIGHT") {
		h = RIGHT;
		w = AGAINSTWIND;
	}
	if (d == "UP") {
		v = UP;
		w = SIDEWIND;
	}
	if (d == "DOWN") {
		v = DOWN;
		w = SIDEWIND;
	}

	//Assign our new value to swap, find its x and y coordinates
	int* newVal = &n->config[y + v][x + h];
	int* newX = &n->tileX[*newVal];
	int* newY = &n->tileY[*newVal];

	//Swap values and their coordinates
	std::swap(*oldX, *newX);
	std::swap(*oldY, *newY);
	std::swap(*oldVal, *newVal);

	n->p = p;                 //Update Parent

	n->g += w;                //Update pathcost based on wind
	n->h = heuristic(*n);     //Update Heuristic
	n->f = n->h + n->g;       //Recalculate f(n)

	n->eX += h;               //Shift x based on horizontal direction
	n->eY += v;				  //Shift y based on vertical direction
	n->ii = insertionIndex++; //Update order of insertion

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



void Agent::findShortestPath() {
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

		//Reassign our pointer to the item at the front of the frontier
		n = frontier.top();
		//Remove from frontier
		frontier.pop();
		//Update explored set
		exploredSet[*n] = n->g;
	}

	//Once we hit our goal we want to push the solution path into the solutionSet
	while (n != nullptr) {
		solutionSet.push(n);
		n = n->p;
	}
}



void Agent::printSolutionSet() {
	//Pop our solution set off the stack
	while (!solutionSet.empty()) {
		solutionSet.top()->printState();
		solutionSet.pop();
	}
}
