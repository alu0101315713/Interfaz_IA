#pragma once

#include "world.h"
#include "taxi.h"

void GetObstacles();
void GetMapSize(unsigned& rows, unsigned& columns);

unsigned EnterNonNegativeNumber(bool include_zero);
float EnterNonNegativeFloat(bool include_zero);

void GetMapSize(unsigned& rows, unsigned& columns);
void GetPosition(unsigned& row, unsigned& column, World& world);
void DisplayObstacleMenu();
void ChooseOption(unsigned& option, int minimum, int maximum);
void DisplayMainMenu();
void AddObstacles(World& world, Taxi& taxi);