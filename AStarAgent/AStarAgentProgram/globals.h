#pragma once
//Board Dimentions, extensibility is limited to 3x3 due to memory limitations of A*
static const unsigned int yAxis = 3;
static const unsigned int xAxis = 3;

//Define the max numbering range for board eg.. 9 (0-8) 
static const unsigned int nTiles = xAxis * yAxis;

//Defines wind strength weights
enum windStrength {
	WITHWIND = 1,
	SIDEWIND = 2,
	AGAINSTWIND = 3,
};

//Defines movement in cartesian directions
enum CartesianDirection {
	LEFT = -1,
	RIGHT = 1,
	UP = -1, //Up is negative because in an Array grid, UP reduces the y index
	DOWN = 1 //Down is positive because in an Array grid, DOWN increases the y index
};