#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <fstream>

#define ROJO "\033[31m█\033[0m"
#define VERDE "\033[32m█\033[0m"
#define AMARILLO "\033[33m█\033[0m"

class Taxi;

class World {
 public:
  World(unsigned& rows, unsigned& columns);
  ~World() {}

  unsigned GetRows();
  unsigned GetColumns();
  unsigned GetFreeCells();
  void GetSurroundings(unsigned& row, unsigned& column, std::vector<bool>& sensor);

  bool CheckIfInBounds(unsigned& row, unsigned& column);
  bool CheckEmpty(unsigned& row, unsigned& column);
  bool CheckPosition(unsigned& row, unsigned& column, Taxi& taxi);
  bool CheckDirection(char& direction);
  void SetObstacle(unsigned& row, unsigned& column, Taxi& taxi);
  void EraseObstacle(unsigned& row, unsigned& column);  
  void SetDirection(unsigned row, unsigned column, char direction);
  void ReadObstaclesFromFile(std::string filename, Taxi& taxi, unsigned& read_obstacles);

  void PrintDirection(unsigned& row, unsigned& column);
  void PrintWorld(Taxi& taxi);

 private:
  std::vector<std::vector<std::string>> world_;
  unsigned rows_;
  unsigned columns_;
  unsigned free_cells_;
};