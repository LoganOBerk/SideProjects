#include "State.h"

void State::setConfig(const int config[yAxis][xAxis]) {
	for (int i = 0; i < yAxis; i++) {
		for (int j = 0; j < xAxis; j++) {
			this->config[i][j] = config[i][j];
		}
	}
}

void State::setCoords(const int config[yAxis][xAxis]) {
	for (int i = 0; i < yAxis; i++) {
		for (int j = 0; j < xAxis; j++) {
			tileX[config[i][j]] = (j + 1);
			tileY[config[i][j]] = (i + 1);
		}
	}
}

void State::moveEmptySpace(const int& dx, const int& dy) {
	// Reassign standard cartesian indexing to 0 based indexing
	const int x = eX - 1;
	const int y = eY - 1;

	// Assigning values we want to change
	int* oldVal = &config[y][x];
	int* oldX = &tileX[*oldVal];
	int* oldY = &tileY[*oldVal];

	// Assign our new value to swap, find its x and y coordinates
	int* newVal = &config[y + dy][x + dx];
	int* newX = &tileX[*newVal];
	int* newY = &tileY[*newVal];

	// Swap values and their coordinates
	std::swap(*oldX, *newX);
	std::swap(*oldY, *newY);
	std::swap(*oldVal, *newVal);

	eX += dx; // Shift x based on horizontal direction
	eY += dy; // Shift y based on vertical direction
}

void State::updateState(State* p, const int& w, const int& h, const int& ii) {
	this->p = p;     // Update parent
	this->g += (w + stepCost);     // Update path cost based on wind
	this->h = h;     // Update heuristic
	this->f = h + g; // Recalculate f(n)
	this->ii = ii;    // Update order of insertion
}

State::State() :
	p(nullptr),
	expO(0),
	g(0),
	h(0),
	f(0),
	eX(0),
	eY(0),
	ii(0),
	config{{0}} {
	for (int t = 0; t < nTiles; t++) {
		tileX[t] = (t % xAxis) + 1;
		tileY[t] = (t / xAxis) + 1;
	}
}

State::State(int config[yAxis][xAxis], State* p, int g) : p(p), g(g) {
	setConfig(config);
	setCoords(config);
	eX = tileX[0];
	eY = tileY[0];
}

bool State::operator==(const State& n) const {
	for (int t = 1; t < nTiles; t++) {
		if (tileX[t] != n.tileX[t] || tileY[t] != n.tileY[t]) {
			return false;
		}
	}
	return true;
}

bool State::operator!=(const State& n) const {
	return !(*this == n);
}

State& State::operator=(const State& n) {
	p = n.p;
	expO = n.expO;
	g = n.g;
	h = n.h;
	f = n.f;

	setConfig(n.config);
	setCoords(n.config);

	eX = n.eX;
	eY = n.eY;

	return *this;
}

void State::printState() const{
	const int expODig = static_cast<int>(std::log10(expO)) + 1;
	const int boardWidth = 3 + xAxis * 2;
	const int expOW = boardWidth - ((expODig + 1) / 2); // Increment width for each extra digit

	for (int i = 0; i < yAxis; i++) {
		std::cout << std::setw(6);
		for (int j = 0; j < xAxis; j++) {
			std::cout << "|";
			if (config[i][j] == 0) std::cout << "-";
			else std::cout << config[i][j];
		}
		std::cout << "|" << std::endl;
	}

	std::cout << std::setw(boardWidth + 2) << "-----" << std::endl;
	std::cout << std::setw(boardWidth - 2) << g << " | " << h << std::endl;
	std::cout << std::setw(expOW) << "#" << expO << std::endl;
	std::cout << std::endl;
}
