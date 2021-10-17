#include "world.h"
#include "taxi.h"



World::World(unsigned& rows, unsigned& columns) {
  rows_ = rows;
  columns_ = columns;
  world_.resize(rows_);
  free_cells_ = (rows * columns) - 2;
  for (unsigned row = 0; row < rows_; ++row) {
    world_[row].resize(columns_);
    for (unsigned column = 0; column < columns_; ++column) {
      world_[row][column] = " ";
    }
  }
}



unsigned
World::GetRows() {
  return rows_;
}



unsigned
World::GetColumns() {
  return columns_;
}



unsigned 
World::GetFreeCells() {
  return free_cells_;
}



// El vector que hace de sensor está ordenado así: [^][<][v][>].
// Cada celda del vector indica si la casilla siguiente en esa dirección está ocupada o no
// Si está ocupada, esa celda del vector contendrá un 1 (true), o un 0 (false) en caso contrario
void
World::GetSurroundings(unsigned& row, unsigned& column, std::vector<bool>& sensor) {
  std::vector<bool> result(4);
  if (CheckIfInBounds(row, column)) {
    sensor[0] = (row == 0) || (world_[row][column] == "█");
    sensor[1] = (column == 0) || (world_[row][column] == "█");
    sensor[2] = (row == (rows_ - 1)) || (world_[row][column] == "█");
    sensor[3] = (column == (columns_ - 1) || (world_[row][column] == "█"));
  }
}



bool 
World::CheckIfInBounds(unsigned& row, unsigned& column) {
  return (row >= 0) && (row < rows_) && (column >= 0) && (column < columns_);
}



bool
World::CheckEmpty(unsigned& row, unsigned& column) {
  return (world_[row][column] != "█");
}



bool 
World::CheckPosition(unsigned& row, unsigned& column, Taxi& taxi) {
  return (CheckIfInBounds(row, column) && CheckEmpty(row, column) && !((row == taxi.GetRow()) && 
         (column == taxi.GetColumn())) && !((row == taxi.GetDestinationRow()) && 
         (column == taxi.GetDestinationColumn())));
}


bool
World::CheckDirection(char& direction) {
  if ((direction == '7') || (direction == '^') || (direction == '9') || 
      (direction == '<') || (direction == '#') || (direction == '>') || 
      (direction == '1') || (direction == 'v') || (direction == '3')) {
    return true;
  } else {
    return false;
  }
}



void
World::SetObstacle(unsigned& row, unsigned& column, Taxi& taxi) {
  unsigned taxi_row = taxi.GetRow();
  unsigned taxi_column = taxi.GetColumn();
  if (CheckPosition(row, column, taxi)) {
    world_[row][column] = "█";
  }
  --free_cells_;
}



void
World::EraseObstacle(unsigned& row, unsigned& column) {
  if ((row >= 0) && (row < rows_) && (column >= 0) && (column < columns_) && (world_[row][column]) == "█") {
    world_[row][column] = " ";
    ++free_cells_;
  }
}



void
World::SetDirection(unsigned row, unsigned column, char direction) {
  world_[row][column] = direction;
}



void
World::ReadObstaclesFromFile(std::string filename, Taxi& taxi, unsigned& read_obstacles) {
  unsigned row, column;
  std::ifstream file(filename);
  char character;
  if (file) {
    while (!file.eof()) {
      file.get(character);
      if ((character >= 48) && (character <= 57)) {
        file.putback(character);
        file >> row;
        file.get(character);
        if (character == ' ') {
          file.get(character);
          if ((character >= 48) && (character <= 57)) {
            file.putback(character);
            file >> column;
            file.get(character);
            if ((character == '\n') || (file.eof())) {
              if ((CheckPosition(row, column, taxi)) && 
                  !((row == taxi.GetRow()) && 
                  (column == taxi.GetColumn()))) {
                SetObstacle(row, column, taxi);
                ++read_obstacles;
              }
            }
          } 
        }
        while ((character != '\n') && !(file.eof())) {
          file.get(character);
        }
      }
    }
    std::cout << "Se completó con éxito la carga de los datos del fichero." << std::endl;
  } else {
    std::cout << "No se pudo abrir el fichero solicitado." << std::endl;
  }
}



void
World::PrintDirection(unsigned& row, unsigned& column) {
  char direction = world_[row][column][0];
  if (CheckDirection(direction)) {
    std::cout << VERDE;
  } else {
    std::cout << " ";
  }
}



void
World::PrintWorld(Taxi& taxi) {
  std::cout << "\nImagen del entorno simulado:" << std::endl;
  for (unsigned row = 0; row < rows_; ++row) {
    for (unsigned column = 0; column < columns_; ++column) {
      if ((row == taxi.GetRow()) && (column == taxi.GetColumn())) {
        std::cout << ROJO;
      } else if ((row == taxi.GetDestinationRow()) && (column == taxi.GetDestinationColumn())) {
        std::cout << AMARILLO;
      } else if ((world_[row][column] == " ") || (world_[row][column] == "█")) {
        std::cout << world_[row][column];
      } else {
        PrintDirection(row, column);
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}