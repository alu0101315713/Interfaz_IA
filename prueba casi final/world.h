#pragma once

//Librerías
#include<vector>
#include<string>
#include<list>
#include<stack>
#include<set>

#include<float.h>
#include<string.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#include<iostream>
#include<fstream>

#include<algorithm>
#include<limits>
#include<chrono>
#include<thread>

//Constantes

const std::string WHITE = "█";                  //Obstaculo.
const std::string BLACK = "\033[30m█\033[0m";   //Nodos.
const std::string RED = "\033[31m█\033[0m";     //Inicio.
const std::string GREEN = "\033[32m█\033[0m";   //Camino (adicional).
const std::string YELLOW = "\033[33m█\033[0m";  //Final.
const std::string CYAN = "\033[36m█\033[0m";    //Camino.

const float DISTANCE = 1.0;
const float DIAGONALDISTANCE = sqrt(2);

//Estructuras de Datos

typedef std::pair<float, std::pair<int, int>> FloatPair;

struct Point {
    int row_ = 0;
    int col_ = 0;
};

struct Node {
    Point parent_;
    float function_ = 0;
    float distance_ = 0;
    float cost_ = 0;
};

struct Taxi {
    Point start_;
    Point end_;
};

//Clases

class World {

    public: 
        World();
        World(int rows, int cols);
        ~World();

        bool isValid(int row, int col);
        bool isEmpty(int row, int col);
        bool isStart(int row, int col);
        bool isEnd(int row, int col);

        void Change(int row, int col, std::string symbol);
        void ClearWorld();
        void ClearObjects();
        void ClearStart();
        void ClearEnd();
        void ClearPath();

        float Manhattan(int row, int col);
        float Diagonal(int row, int col);
        float Euclidean(int row, int col);

        void AStar(int mode, int heuristic, int speed);
        void Path(int speed);

        void Visualizer();
        void MapVisualizer();
        void TaxiVisualizer();

    private:
        int rows_;
        int cols_;
        Taxi taxi_;
        std::vector<std::vector<std::string>> world_;
        std::vector<std::vector<Node>> map_;
};