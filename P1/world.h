#pragma once

#include "taxi.h"

class World {
 public:
  World(unsigned& rows, unsigned& columns);
  ~World() {}

  unsigned GetRows();
  unsigned GetColumns();


  bool CheckPosition(unsigned& row, unsigned& column, Taxi& taxi);
  //bool CheckDirection(char& direction);
  void SetObstacle(unsigned& row, unsigned& column, Taxi& taxi);
  void SetDirection(unsigned row, unsigned column, char direction);
  void ReadObstaclesFromFile(std::string filename, Taxi& taxi);

  void PrintDirection(unsigned& row, unsigned& column);
  void PrintWorld(Taxi& taxi);


 private:
  std::vector<std::vector<std::string>> world_;
  unsigned rows_;
  unsigned columns_;
};









