/*
# Author: Logan Berk
# Creation Date     : 1 / 23 / 2026
# Modification Date : 1 / 24 / 2026
# Purpose           : Code for Simple Agent used to solve Windy 8-Puzzle Problem with A*
#
# Modification Date : 1 / 25 / 2026
# Purpose           : Modified State class to have arrays that contain x and y coordinates to reduce
#                     time complexity of locX and locY functions from O(N^2) to O(1), and in turn giving ability
#                     to reduce the time complexity of tilesOutOfPlace function from O(N^2) to O(N)
#
# Modification Date : 2 / 2 / 2026
# Purpose           : Added UI as a separate implementation and allowed user to input their desired board;
#                     also solved program bug—when a solution can’t be found we output “solution not found”
#                     and the number of configurations that were tried
*/

#include "UI.h"

int main() {
	// Set up board states
	int initConfig[yAxis][xAxis]{};
	int goalConfig[yAxis][xAxis]{};

	// Allow user to set board states
	collectInitalAndGoalInputs(initConfig, goalConfig);

	// Pass board states to the agent
	AStarAgent a(initConfig, goalConfig);

	// Tell the agent to find the shortest path
	a.findShortestPath();

	// Print the agent's result
	printSolution(a);

	return 0;
}
