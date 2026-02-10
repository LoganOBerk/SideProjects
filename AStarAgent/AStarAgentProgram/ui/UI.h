#pragma once

#include <array>
#include <string>
#include "AStarAgent.h"

// Basic UI functionality for user input handling
void printBoardRules();
void printSolution(Agent&);

const int collectValidTileInput(bool(&)[nTiles]);
void collectConfigInput(int(&)[yAxis][xAxis]);
void collectInitalAndGoalInputs(int(&)[yAxis][xAxis], int(&)[yAxis][xAxis]);
