/*
# Author: Logan Berk
# Creation Date : 1 / 23 / 2026
# Modification Date : 1 / 24 / 2026
# Purpose : Code for Simple Agent used to solve Windy 8-Puzzle Problem with A*
#
# Modification Date : 1 / 25 / 2026
# Purpose : Modified State class to have arrays that contain x and y coordinates to reduce
# time complexity of locX and locY functions from O(N^2) to O(1), and in turn giving ability
# to reduce the time complexity of tilesOutOfPlace function from O(N^2) to O(N)
#
*/

#include "agent.h"


int main() {
	int initConfig[yAxis][xAxis] = { { 6,5,3 },
									 { 7,1,4 },
									 { 8,0,2 } };

	int goalConfig[yAxis][xAxis] = { { 1,6,8 },
									 { 2,0,5 },
									 { 4,7,3 } };

	Agent a(initConfig, goalConfig);
	a.findShortestPath();
	a.printSolutionSet();


	return 0;
}