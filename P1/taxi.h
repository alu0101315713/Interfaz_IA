#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <fstream>

#define ROJO "\033[31m█\033[0m"
#define VERDE "\033[32m█\033[0m"

class Taxi {
 public:
  Taxi(unsigned& initial_row, unsigned& initial_column);
  ~Taxi() {}

  unsigned GetRow();
  unsigned GetColumn();

  void Travel(unsigned& row, unsigned& column);




 private:
  unsigned row_;
  unsigned column_;


};