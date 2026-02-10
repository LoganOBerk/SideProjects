#pragma once

// Board dimensions, extensibility is limited to 3x3 due to memory limitations of A*
static const int yAxis = 3;
static const int xAxis = 3;

// Define the max numbering range for board eg. 9 (0–8)
static const int nTiles = xAxis * yAxis;

// Defines wind strength weights
enum windStrength {
	WESTWIND = 3,
	NORTHWIND = 2,
	SOUTHWIND = 2,
	EASTWIND = 1,
};

// Defines movement in cartesian directions
enum CartesianDirection {
	WEST = -1,
	EAST = 1,
	NORTH = -1, // NORTH is negative because in an array grid, NORTH reduces the y index
	SOUTH = 1   // SOUTH is positive because in an array grid, SOUTH increases the y index
};
