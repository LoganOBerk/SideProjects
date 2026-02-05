#include "UI.h"

// User explanation of expectations related to input
void printBoardRules() {
	static bool ran = false;
	std::string state = (ran) ? "GOAL" : "INITIAL";

	std::cout << "Please enter a valid " << state << " board configuration." << std::endl;
	std::cout << "====================================================================================================================" << std::endl;
	std::cout << "Valid board configurations have " << nTiles << " numbers (" << 0 << "-" << nTiles - 1 << ") without repeating numbers." << std::endl;
	std::cout << "====================================================================================================================" << std::endl;

	ran = true;
}

// Ensures that the user can only input valid tiles; if not, nothing happens
const int collectValidTileInput(bool(&isPlaced)[nTiles]) {
	char c;
	int x = 0;
	while (true) {
		c = _getch();
		if (c < '0' || c >= nTiles + '0') continue;
		x = c - '0';

		if (isPlaced[x]) continue;
		isPlaced[x] = true;
		return x;
	}
}

// Accepts a 2D array of size XxY and modifies it based on user input
void collectConfigInput(int(&config)[yAxis][xAxis]) {
	// Tracking if a tile was placed, indexed by unique tile value
	bool isPlaced[nTiles]{ false };

	printBoardRules();

	int x = 0;
	for (int i = 0; i < yAxis; i++) {
		for (int j = 0; j < xAxis; j++) {
			std::cout << '|';
			x = collectValidTileInput(isPlaced);

			// Populate the config
			config[i][j] = x;
			std::cout << x;
		}
		std::cout << '|' << std::endl;
	}

	std::cout << std::endl;
}

// Specifically prompts user twice: once for initial state, another for goal state
void collectInitalAndGoalInputs(int(&init)[yAxis][xAxis], int(&goal)[yAxis][xAxis]) {
	collectConfigInput(init);
	collectConfigInput(goal);
}

// Prints the solution set result provided by the agent
void printSolution(Agent& a) {
	std::cout << "===================" << std::endl;
	std::cout << "Agent Solution Path" << std::endl;
	std::cout << "===================" << std::endl;
	std::cout << std::endl;

	a.printSolutionSet();
}
