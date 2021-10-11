#include "world.h"

void WorldError() {
    std::cout << "Inserte valores dentro del rango." << std::endl;
    exit(1);
}

World::World(int xSize, int ySize) {
    if ((xSize < 1) || (ySize < 1)) {
        WorldError();
    }
    xSize_ = xSize;
    ySize_ = ySize;
    std::vector<char> aux;
    aux.resize(xSize_);
    for (int i = 0; i < xSize_; i++) {
        aux[i] = ' ';
    }
    for (int i = 0; i < ySize_; i++) {
        world_.push_back(aux);
    }
}

World::~World() {
    world_.clear();
}

void World::Change(int xPosition, int yPosition) {
    if (((xPosition < 0) || (xPosition >= xSize_)) || ((yPosition < 0) || (yPosition >= ySize_))) {
        WorldError();
    }
    if (world_[yPosition][xPosition] == ' '){
        world_[yPosition][xPosition] = 'x';
    } else if (world_[yPosition][xPosition] == 'x') {
        world_[yPosition][xPosition] = ' ';
    }
}

void World::Set(int xPosition, int yPosition, char symbol) {
    if (((xPosition < 0) || (xPosition >= xSize_)) || ((yPosition < 0) || (yPosition >= ySize_))) {
        WorldError();
    }
    if ((symbol == 'F') && (world_[yPosition][xPosition] == 'S')) {
        std::cout << "Esa posicion es la salida." << std::endl;
        exit(1);
    }
    world_[yPosition][xPosition] = symbol;
}

void World::Visualizer() {
  std::cout << std::endl;
  std::cout << "Imagen del mundo finito: " << std::endl;
  for (int i = 0; i < world_.size(); i++) {
    for (int j = 0; j < world_[i].size(); j++)
      std::cout << world_[i][j];
    std::cout << std::endl;  
  }
  std::cout << std::endl;
}