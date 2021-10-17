#include "taxi.h"
#include "world.h"



Taxi::Taxi(unsigned& initial_row, unsigned& initial_column, 
           unsigned& destination_row, unsigned& destination_column,
           World& world):
sensor_(4)
{
  row_ = initial_row;
  column_ = initial_column;
  destination_row_ = destination_row;
  destination_column_ = destination_column;
  world.GetSurroundings(initial_row, initial_column, sensor_);
  movement_mode_ = false;
}



void
Taxi::SetRow(unsigned& row) {
  row_ = row;
}



void
Taxi::SetColumn(unsigned& column) {
  column_ = column;
}



void
Taxi::SetDestinationRow(unsigned& row) {
  destination_row_ = row;
}



void
Taxi::SetDestinationColumn(unsigned& column) {
  destination_column_ = column;
}



void
Taxi::SetMovementMode(bool mode) {
  movement_mode_ = mode;
}



unsigned
Taxi::GetRow() {
  return row_;
}



unsigned
Taxi::GetColumn() {
  return column_;
}



unsigned
Taxi::GetDestinationRow() {
  return destination_row_;
}



unsigned
Taxi::GetDestinationColumn() {
  return destination_column_;
}



void
Taxi::Travel(unsigned& row, unsigned& column) {
  row_ = row;
  column_ = column;
}