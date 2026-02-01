#include <iostream>
#include "globals.h"
#pragma once
//State class used to represent the state of the game currently
class State {
	friend class Agent;
private:
	State* p;                 //Parent game state
	int expO;                 //Order of expansion, when popped from queue
	int config[yAxis][xAxis]; //Current board configuration
	int tileX[nTiles];        //Array is indexed as tile numbers, with the value inside being corresponding x coordinate
	int tileY[nTiles];        //Array is indexed as tile numbers, with the value inside being corresponding y coordinate

	int g;                    //g(n), the total path cost so far
	int h;                    //h(n), the current heuristic for configuration
	int f;					  //Evaluation function f(n) = h(n) + g(n) used for priority sorting

	int eX;                   //Empty space X coordinate
	int eY;                   //Empty space Y coordinate
	int ii;                   //Insertion index, identifies the order for FIFO in ties (tie breaker)

public:
	//Constructors
	State();
	State(int[yAxis][xAxis], State* p = nullptr, int g = 0);

	//Setters for board configuration	
	void setConfig(const int[yAxis][xAxis]);
	void setCoords(const int[yAxis][xAxis]);

	void moveTile(int, int);
	void updateState(State*, int, int, int);

	//Prints gamestate values including board config in predefined manner
	void printState();

	//Necessary overloaded operators and functors
	State& operator=(const State& n);
	bool operator==(const State& n) const;
	bool operator!=(const State& n) const;
	struct StateHash;  //Used to avoid collisions in unordered_map using a simple hash
	struct Comparator; //Used to define minheap ordering and FIFO in ties
};

struct State::StateHash {
	std::size_t operator()(const State& s) const {
		std::size_t h = 0;
		for (int t = 1; t < nTiles; t++) { // skip empty tile
			h = h * 31 + std::hash<int>()(s.tileX[t]);
			h = h * 31 + std::hash<int>()(s.tileY[t]);
		}
		return h;
	}
};



struct State::Comparator {
	bool operator()(const State* a, const State* b) const {
		//If states are equal break tie with FIFO otherwise order in minheap fashion based on smallest f(n)
		return (a->f == b->f) ? a->ii > b->ii : a->f > b->f;
	}
};
