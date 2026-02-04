#pragma once

#include <iomanip>
#include <iostream>

#include "Globals.h"

// State class used to represent the state of the game currently, 
// contains many different variables that allow for tracking various components of game state as needed
class State {
	// Direct access is used here to reduce verbosity and overhead for tight search loops
	friend class Agent;
	friend class AStarAgent;

private:
	// Parent game state
	State* p;

	// Order of expansion, when popped from queue
	int expO;

	// Current board configuration
	int config[yAxis][xAxis];

	// Arrays indexed as tile numbers, with the value inside being corresponding coordinates
	int tileX[nTiles];
	int tileY[nTiles];

	// g(n), h(n), and evaluation function f(n) = h(n) + g(n)
	int g;
	int h;
	int f;

	// Empty space coordinates
	int eX;
	int eY;

	// Insertion index, identifies the order for FIFO in ties (tie breaker)
	int ii;

public:
	// Constructors
	State();
	State(int[yAxis][xAxis], State* p = nullptr, int g = 0);

	// Setters for board configuration
	void setConfig(const int[yAxis][xAxis]);
	void setCoords(const int[yAxis][xAxis]);

	void moveTile(int, int);
	void updateState(State*, int, int, int);

	// Prints gamestate values including board config in predefined manner
	void printState();

	// Necessary overloaded operators and functors
	State& operator=(const State& n);
	bool operator==(const State& n) const;
	bool operator!=(const State& n) const;

	struct StateHash;   // Used to avoid collisions in unordered_map using a simple hash
	struct Comparator; // Used to define minheap ordering and FIFO in ties
};

struct State::StateHash {
	std::size_t operator()(const State& s) const {
		std::size_t h = 0;
		for (int t = 1; t < nTiles; t++) { // Skip empty tile
			h = h * 31 + std::hash<int>()(s.tileX[t]);
			h = h * 31 + std::hash<int>()(s.tileY[t]);
		}
		return h;
	}
};

struct State::Comparator {
	bool operator()(const State* a, const State* b) const {
		// If states are equal break tie with FIFO otherwise order in minheap fashion based on smallest f(n)
		return (a->f == b->f) ? a->ii > b->ii : a->f > b->f;
	}
};
