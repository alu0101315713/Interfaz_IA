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

//Colores que aparecerán en el mapa (Las adicionales no se usan actualmente).
const std::string BLACK = "\033[30m██\033[0m";    //Adicional.
const std::string RED = "\033[31m██\033[0m";      //Inicio.
const std::string GREEN = "\033[32m██\033[0m";    //Camino.
const std::string YELLOW = "\033[33m██\033[0m";   //Final.
const std::string BLUE = "\033[34m██\033[0m";     //Nodos.
const std::string MAGENTA = "\033[35m██\033[0m";  //Adicional.
const std::string CYAN = "\033[36m██\033[0m";     //Adicional.
const std::string WHITE = "\033[37m██\033[0m";    //Obstaculo.

//Distancias entre los nodos del mapa.
const float DISTANCE = 1.0;
const float DIAGONALDISTANCE = sqrt(2);

//Estructuras de Datos

typedef std::pair<float, std::pair<int, int>> FloatPair;

//Estructura que define las posiciones del mapa.
struct Point {
    int row_ = 0;
    int col_ = 0;
};

//Estructura que define el contenido de cada una de las posiciones del mapa.
struct Node {
    Point parent_;
    float function_ = 0;
    float distance_ = 0;
    float cost_ = 0;
};

//Estructura que define el inicio y el final del camino.
struct Taxi {
    Point start_;
    Point end_;
};

//Clases

//Clase que define el mundo.
class World {

    public: 
        //Constructores y destructor.
        World();
        World(int rows, int cols);
        ~World();

        //Funciones para comprobar posiciones del mundo.
        bool isValid(int row, int col);
        bool isEmpty(int row, int col);
        bool isStart(int row, int col);
        bool isEnd(int row, int col);

        //Funciones para modificar el mundo.
        void Change(int row, int col, std::string symbol);
        void ClearWorld();
        void ClearObjects();
        void ClearStart();
        void ClearEnd();
        void ClearPath();

        //Funciones heurísticas.
        float Manhattan(int row, int col);
        float Diagonal(int row, int col);
        float Euclidean(int row, int col);

        //Funciones del algoritmo A*.
        void AStar(int mode, int heuristic, int speed);
        void Path(int speed);

        //Visualizadores.
        void Visualizer();
        void MapVisualizer();
        void TaxiVisualizer();

    private:
        int rows_;
        int cols_;
        Taxi taxi_;                                             
        std::vector<std::vector<std::string>> world_;           //Mapa que define la visión física del mundo.
        std::vector<std::vector<Node>> map_;                    //Mapa que define la visión virtual del mundo.
};