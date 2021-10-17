#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <fstream>

#define ROJO "\033[31m█\033[0m"
#define VERDE "\033[32m█\033[0m"
#define AMARILLO "\033[33m█\033[0m"


class World;

class Taxi {
 public:
  Taxi(unsigned& initial_row, unsigned& initial_column, unsigned& destination_row, 
       unsigned& destination_column, World& world);
  ~Taxi() {}

  void SetRow(unsigned& row);
  void SetColumn(unsigned& column);
  void SetDestinationRow(unsigned& row);
  void SetDestinationColumn(unsigned& column);
  void SetMovementMode(bool mode);

  unsigned GetRow();
  unsigned GetColumn();
  unsigned GetDestinationRow();
  unsigned GetDestinationColumn();  

  void Travel(unsigned& row, unsigned& column);

 private:
  unsigned row_;
  unsigned column_;
  unsigned destination_row_;
  unsigned destination_column_;
  std::vector<bool> sensor_;
  bool movement_mode_; // false = puede moverse en 4 direcciones (el taxi se crea en este modo)
                       // true = puede moverse en 8 direcciones
};