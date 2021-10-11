#include "world.h"

void GetObstacles();
void GetMapSize(unsigned& rows, unsigned& columns);
unsigned EnterNonNegativeNumber(bool include_zero);
void GetMapSize(unsigned& rows, unsigned& columns);
void GetPosition(unsigned& row, unsigned& column, World& world, Taxi& taxi);
void DisplayObstacleMenu();
void ChooseObstacleOption(unsigned& option);
void DisplayMainMenu();
void ChooseMainOption(unsigned& option);