#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<chrono>
#include<thread>
#include<exception>


class World {
  public:
    World(int xSize, int ySize);
    ~World();
    void Change(int xPosition, int yPosition);
    void Set(int xPosition, int yPosition, char symbol);
    void Visualizer();
    friend void WorldError();

  private:
    std::vector<std::vector<char>> world_;
    int xSize_;
    int ySize_;
};