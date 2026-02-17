#pragma once
#if defined(__linux__)
	#include <ncurses.h>
#else
	#include <conio.h>
#endif



// Board dimensions, extensibility is limited to 3x3 due to memory limitations of A*
static const int yAxis = 3;
static const int xAxis = 3;

// Define the max numbering range for board eg. 9 (0–8)
static const int nTiles = xAxis * yAxis;

#define WINDIRWEST 1
#define WINDIREAST 0
#define WINDIRNORTH 0
#define WINDIRSOUTH 0

//Cost of a standard move with no wind
static const int stepCost = 1;

//Base wind strength values
constexpr const int str = 2; //Base Wind Strength
constexpr const int op = 0;  //Opposing Wind Strength



//Wind strength calculations
constexpr const int oppWin = op; //Strength of the opposing wind
constexpr const int windStr = str - op; //Strength of the wind
constexpr const int sideWin = windStr/2; //Strength of perpendicular wind



// Defines wind strength weights (cost to move in opposite direction)
enum windStrength {
#if WINDIRWEST
	WESTWIND = windStr,  
	EASTWIND = oppWin,
	NORTHWIND = sideWin, 
	SOUTHWIND = sideWin, 
#elif WINDIREAST
	EASTWIND = winStr,
	WESTWIND = oppWin,  
	NORTHWIND = sideWin, 
	SOUTHWIND = sideWin, 
#elif WINDIRNORTH
	NORTHWIND = windStr, 
	SOUTHWIND = oppWin, 
	WESTWIND = sideWin,
	EASTWIND = sideWin,  
#elif WINDIRSOUTH
	SOUTHWIND = windStr,
	NORTHWIND = oppWin, 
	EASTWIND = sideWin,  
	WESTWIND = sideWin,
#else
	SOUTHWIND = 0,
	NORTHWIND = 0,
	EASTWIND = 0,
	WESTWIND = 0,
#endif

};

// Defines movement in cartesian directions
enum CartesianDirection {
	WEST = -1,
	EAST = 1,
	NORTH = -1, // NORTH is negative because in an array grid, NORTH reduces the y index
	SOUTH = 1   // SOUTH is positive because in an array grid, SOUTH increases the y index
};
