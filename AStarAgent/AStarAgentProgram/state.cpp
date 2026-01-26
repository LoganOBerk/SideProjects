#include "state.h"

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



State::State()
	: p(nullptr), expO(0), g(0), h(0), f(0),
	eX(0), eY(0), ii(0),
	config{ {0,0,0}, {0,0,0}, {0,0,0} },
	tileX{ 1,2,3,1,2,3,1,2,3 },
	tileY{ 1,2,3,1,2,3,1,2,3 }
{}



State::State(State* p, int expO, int g, int h, int ii, int config[yAxis][xAxis]) : p(p), expO(expO), g(g), h(h), ii(ii) {
	setConfig(config);
	setCoords(config);
	f = g + h;
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



void State::printState() {
	for (int i = 0; i < yAxis; i++) {
		for (int j = 0; j < xAxis; j++) {
			(config[i][j] == 0) ? std::cout << "-" : std::cout << config[i][j]; std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << g << " | " << h << std::endl;
	std::cout << " #" << expO << std::endl;
	std::cout << std::endl;
}