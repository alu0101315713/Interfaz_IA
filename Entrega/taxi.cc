#include "taxi.h"

Taxi::Taxi(unsigned& initial_row, unsigned& initial_column) {
  row_ = initial_row;
  column_ = initial_column;
}

unsigned
Taxi::GetRow() {
  return row_;
}

unsigned
Taxi::GetColumn() {
  return column_;
}

void
Taxi::Travel(unsigned& row, unsigned& column) {
  row_ = row;
  column_ = column;
}