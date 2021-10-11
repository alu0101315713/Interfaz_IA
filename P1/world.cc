#include "world.h"

World::World(unsigned& rows, unsigned& columns) {
  rows_ = rows;
  columns_ = columns;
  world_.resize(rows_);
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



bool 
World::CheckPosition(unsigned& row, unsigned& column, Taxi& taxi) {
  bool world_ok = false;
  if ((row == taxi.GetRow()) && (column == taxi.GetColumn())) {
    return false;
  } else {
    if ((row >= 0) && (row < rows_) && (column >= 0) && (column < columns_) && 
        (world_[row][column] != "█") && 
        (world_[row][column] != "\033[31m█\033[0m")) {
      return true;
    } else {
      return false;
    }
  }
}


/*
bool
World::CheckDirection(char& direction) {
  
}
*/


void
World::SetObstacle(unsigned& row, unsigned& column, Taxi& taxi) {
  unsigned taxi_row = taxi.GetRow();
  unsigned taxi_column = taxi.GetColumn();
  if (CheckPosition(row, column, taxi)) {
    world_[row][column] = "█";
  }
}



void
World::SetDirection(unsigned row, unsigned column, char direction) {
  world_[row][column] = direction;
}



void
World::ReadObstaclesFromFile(std::string filename, Taxi& taxi) {
  unsigned row, column;
  std::ifstream file(filename);
  if (file) {
    while (!file.eof()) {
      file >> row >> column;
      if ((CheckPosition(row, column, taxi)) && 
          !((row == taxi.GetRow()) && 
          (column == taxi.GetColumn()))) {
        SetObstacle(row, column, taxi);
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
  switch (direction) {
    case '1':
      //std::cout << "\u2199";
      std::cout << VERDE;
      break;
    case 'v':
      //std::cout << "\u2193";
      std::cout << VERDE;
      break;
    case '3':
      //std::cout << "\u2198";
      std::cout << VERDE;
      break;
    case '<':
      //std::cout << "\u2190";
      std::cout << VERDE;
      break;
    case '#':
      std::cout << 'X';
      break;
    case '>':
      //std::cout << "\u2192";
      std::cout << VERDE;
      break;
    case '7':
      //std::cout << "\u2196";
      std::cout << VERDE;
      break;
    case '^':
      //std::cout << "\u2191";
      std::cout << VERDE;
      break;
    case '9':
      //std::cout << "\u2197";
      std::cout << VERDE;
      break;
    default:
      std::cout << " ";
      break;
  }
}



void
World::PrintWorld(Taxi& taxi) {
  for (unsigned row = 0; row < rows_; ++row) {
    for (unsigned column = 0; column < columns_; ++column) {
      if ((row == taxi.GetRow()) && (column == taxi.GetColumn())) {
        std::cout << "\033[31m█\033[0m";
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