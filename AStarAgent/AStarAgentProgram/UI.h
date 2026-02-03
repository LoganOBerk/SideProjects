#pragma once
#include "agent.h"

#include <conio.h>
#include <string>
#include <array>
#include <bitset>

//Basic UI functionality for user input handling
void printBoardRules();
int collectValidTileInput(std::bitset<nTiles>&);
void acceptConfigInput(int(&)[yAxis][xAxis]);
void acceptInitalAndGoalInputs(int(&)[yAxis][xAxis], int(&)[yAxis][xAxis]);
void printSolution(Agent&);