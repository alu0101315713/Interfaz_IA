#include "world.h"

void WorldError() {
    std::cout << "Inserte valores dentro del rango." << std::endl;
    exit(1);
}

World::World() {
    rows_ = 20;
    cols_ = 35;
    std::vector<std::string> aux;
    std::vector<Node> aux_map;
    aux.resize(cols_);
    aux_map.resize(cols_);
    for (int i = 0; i < cols_; i++) {
        aux[i] = " ";
    }
    for (int i = 0; i < rows_; i++) {
        world_.push_back(aux);
        map_.push_back(aux_map);
    }
}

World::World(int rows, int cols) {
    if ((rows < 1) || (cols < 1)) {
        WorldError();
    }
    rows_ = rows;
    cols_ = cols;
    std::vector<std::string> aux;
    std::vector<Node> aux_map;
    aux.resize(cols_);
    aux_map.resize(cols_);
    for (int i = 0; i < cols_; i++) {
        aux[i] = " ";
    }
    for (int i = 0; i < rows_; i++) {
        world_.push_back(aux);
        map_.push_back(aux_map);
    }
}

World::~World() {
    world_.clear();
    map_.clear();
}

bool World::isValid(int row, int col) {
    return ((row >= 0) && (row < rows_) && (col >= 0) && (col < cols_));
    if ((row < 0) || (row >= rows_) || (col < 0) || (col >= cols_)) {
        return false;
    } else {
        return true;
    }
}

bool World::isEmpty(int row, int col) {
    if (isValid(row, col) == false) {
        WorldError();
    }
    if (world_[row][col] == WHITE) {
        return false;
    } else {
        return true;
    }
}

bool World::isStart(int row, int col) {
    if (isValid(row, col) == false) {
        WorldError();
    }
    if ((row == taxi_.start_.row_) && (col == taxi_.start_.col_)) {
        return true;
    } else {
        return false;
    }
}

bool World::isEnd(int row, int col) {
    if (isValid(row, col) == false) {
        WorldError();
    }
    if ((row == taxi_.end_.row_) && (col == taxi_.end_.col_)) {
        return true;
    } else {
        return false;
    }
}

void World::Change(int row, int col, std::string symbol) {
    if (isValid(row, col) == false) {
        WorldError();
    }
    if (symbol == RED) {
        taxi_.start_.row_ = row;
        taxi_.start_.col_ = col;
    } else if (symbol == YELLOW) {
        taxi_.end_.row_ = row;
        taxi_.end_.col_ = col;
    }
    world_[row][col] = symbol;
}

void World::ClearWorld() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            world_[i][j] = " ";
        } 
    }
    taxi_.start_.row_ = 0;
    taxi_.start_.col_ = 0;
    taxi_.end_.row_ = 0;
    taxi_.end_.col_ = 0;
}

void World::ClearObjects() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (world_[i][j] == WHITE)
                world_[i][j] = " ";
        } 
    }
}

void World::ClearStart() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (world_[i][j] == RED)
                world_[i][j] = " ";
        } 
    }
    taxi_.start_.row_ = 0;
    taxi_.start_.col_ = 0;
}

void World::ClearEnd() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (world_[i][j] == YELLOW)
                world_[i][j] = " ";
        } 
    }
    taxi_.end_.row_ = 0;
    taxi_.end_.col_ = 0;
}

void World::ClearPath() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if ((world_[i][j] == CYAN) || (world_[i][j] == BLACK))
                world_[i][j] = " ";
        } 
    }
}

float World::Manhattan(int row, int col) {
    return abs(row - taxi_.end_.row_) + abs(col - taxi_.end_.col_);
}

float World::Diagonal(int row, int col) {
    float dx = abs(row - taxi_.end_.row_);
    float dy = abs(col - taxi_.end_.col_);
    return DISTANCE * (dx + dy) + (DIAGONALDISTANCE - 2 * DISTANCE) * fmin(dx, dy);
}

float World::Euclidean(int row, int col) {
    return sqrt((row - taxi_.end_.row_) * (row - taxi_.end_.row_) + (col - taxi_.end_.col_) * (col - taxi_.end_.col_));
}

void World::Path(int speed) {
    std::chrono::_V2::system_clock::time_point time;
    int timeint = speed;
    std::cout << std::endl << "El camino es el siguiente: " << std::endl;
    std::stack<Point> Path;
    Point destination, temporal;

    destination.row_ = taxi_.end_.row_;
    destination.col_ = taxi_.end_.col_;

    while (!((map_[destination.row_][destination.col_].parent_.row_ == destination.row_) && (map_[destination.row_][destination.col_].parent_.col_ == destination.col_))) {
        Path.push(destination);
        temporal.row_ = map_[destination.row_][destination.col_].parent_.row_;
        temporal.col_ = map_[destination.row_][destination.col_].parent_.col_;
        destination.row_ = temporal.row_;
        destination.col_ = temporal.col_;
    }

    Path.push(destination);
    while (!Path.empty()) {
        //time = std::chrono::system_clock::now();
        temporal.row_ = Path.top().row_;
        temporal.col_ = Path.top().col_;
        Path.pop();
        for (int i = 0; i < world_.size(); i++) {
            for (int j = 0; j < world_[i].size(); j++) {
                if ((world_[i][j] != RED) && (world_[i][j] != YELLOW) && (world_[i][j] != CYAN)) {
                    if (map_[i][j].function_ != FLT_MAX)
                        world_[i][j] = BLACK;
                    if ((temporal.row_ == i) && (temporal.col_ == j)) 
                        world_[i][j] = CYAN;
                }
            } 
        }
        //time += std::chrono::milliseconds(1000 / timeint);
        //std::this_thread::sleep_until(time);
        system("clear");
        Visualizer();
    }

    return;
}

void World::AStar(int mode, int heuristic, int speed) {
    //Será verdadero cuando se encuentre la meta.
    bool isDestination = false;
    float cost, distance, function;
    //Comprobamos si estamos en la meta.
    if (isEnd(taxi_.start_.row_, taxi_.start_.col_) == true) {
        std::cout << std::endl << "Nos encontramos en la meta. " << std::endl;
        isDestination = true;
        return;
    }
    //Lista cerrada inicializada a falso, ya que ningún nodo ha sido incluido.
    bool ClosedList[rows_][cols_];
    memset(ClosedList, false, sizeof(ClosedList));

    int row, col;
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            map_[i][j].function_ = FLT_MAX;
            map_[i][j].cost_ = FLT_MAX;
            map_[i][j].distance_ = FLT_MAX;
            map_[i][j].parent_.row_ = -1;
            map_[i][j].parent_.col_ = -1;
        }
    }
    //Parámetros del nodo inicial.
    row = taxi_.start_.row_;
    col = taxi_.start_.col_;
    map_[row][col].function_ = 0;
    map_[row][col].cost_ = 0;
    map_[row][col].distance_ = 0;
    map_[row][col].parent_.row_ = row;
    map_[row][col].parent_.col_ = col;

    //Lista abierta en la que se guardan las funciones y las posiciones a examinar.
    std::set<FloatPair> OpenList;
    FloatPair temporal, begin;

    //Colocamos la celda inicial en la lista para examinarla.
    temporal.first = 0;
    temporal.second.first = row;
    temporal.second.second = col;
    OpenList.insert(temporal);

    //Mientras la lista no esté vacía, se seguirá ejecutando.
    while (OpenList.empty() == false) {
        begin = *OpenList.begin();
        OpenList.erase(OpenList.begin());

        row = begin.second.first;
        col = begin.second.second;
        ClosedList[row][col] = true;

        //Primer Sucesor (Norte)
        if (isValid(row - 1, col) == true) {
            //En caso de que la siguiente posición sea la final.
            if (isEnd(row - 1, col) == true) {
                map_[row - 1][col].parent_.row_ = row;
                map_[row - 1][col].parent_.col_ = col;
                std::cout << std::endl << "Se ha encontrado la meta." << std::endl;
                Path(speed);
                isDestination = true;
                return;
            }
            //En caso contrario.
            if ((ClosedList[row - 1][col] == false) && (isEmpty(row - 1, col) == true)) {
                cost = map_[row][col].cost_ + 1;
                if (heuristic == 1) {
                    distance = Manhattan(row - 1, col);
                } else if (heuristic == 2) {
                    distance = Euclidean(row - 1, col);
                } else if (heuristic == 3) {
                    distance = Diagonal(row - 1, col);
                } 
                function = cost + distance;
                //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                if ((map_[row - 1][col].function_ == FLT_MAX) || (map_[row - 1][col].function_ > function)) {
                    temporal.first = function;
                    temporal.second.first = row - 1;
                    temporal.second.second = col;
                    OpenList.insert(temporal);

                    map_[row - 1][col].function_ = function;
                    map_[row - 1][col].cost_ = cost;
                    map_[row - 1][col].distance_ = distance;
                    map_[row - 1][col].parent_.row_ = row;
                    map_[row - 1][col].parent_.col_ = col;
                }    
            }
        }
        //Segundo Sucesor (Este)
        if (isValid(row, col + 1) == true) {
            //En caso de que la siguiente posición sea la final.
            if (isEnd(row, col + 1) == true) {
                map_[row][col + 1].parent_.row_ = row;
                map_[row][col + 1].parent_.col_ = col;
                std::cout << std::endl << "Se ha encontrado la meta." << std::endl;
                Path(speed);
                isDestination = true;
                return;
            }
            //En caso contrario.
            if ((ClosedList[row][col + 1] == false) && (isEmpty(row, col + 1) == true)) {
                cost = map_[row][col].cost_ + 1;
                if (heuristic == 1) {
                    distance = Manhattan(row, col + 1);
                } else if (heuristic == 2) {
                    distance = Euclidean(row, col + 1);
                } else if (heuristic == 3) {
                    distance = Diagonal(row, col + 1);
                } 
                function = cost + distance;
                //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                if ((map_[row][col + 1].function_ == FLT_MAX) || (map_[row][col + 1].function_ > function)) {
                    temporal.first = function;
                    temporal.second.first = row;
                    temporal.second.second = col + 1;
                    OpenList.insert(temporal);

                    map_[row][col + 1].function_ = function;
                    map_[row][col + 1].cost_ = cost;
                    map_[row][col + 1].distance_ = distance;
                    map_[row][col + 1].parent_.row_ = row;
                    map_[row][col + 1].parent_.col_ = col;
                }    
            }
        }
        //Tercer Sucesor (Sur)
        if (isValid(row + 1, col) == true) {
            //En caso de que la siguiente posición sea la final.
            if (isEnd(row + 1, col) == true) {
                map_[row + 1][col].parent_.row_ = row;
                map_[row + 1][col].parent_.col_ = col;
                std::cout << std::endl << "Se ha encontrado la meta." << std::endl;
                Path(speed);
                isDestination = true;
                return;
            }
            //En caso contrario.
            if ((ClosedList[row + 1][col] == false) && (isEmpty(row + 1, col) == true)) {
                cost = map_[row][col].cost_ + 1;
                if (heuristic == 1) {
                    distance = Manhattan(row + 1, col);
                } else if (heuristic == 2) {
                    distance = Euclidean(row + 1, col);
                } else if (heuristic == 3) {
                    distance = Diagonal(row + 1, col);
                } 
                function = cost + distance;
                //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                if ((map_[row + 1][col].function_ == FLT_MAX) || (map_[row + 1][col].function_ > function)) {
                    temporal.first = function;
                    temporal.second.first = row + 1;
                    temporal.second.second = col;
                    OpenList.insert(temporal);

                    map_[row + 1][col].function_ = function;
                    map_[row + 1][col].cost_ = cost;
                    map_[row + 1][col].distance_ = distance;
                    map_[row + 1][col].parent_.row_ = row;
                    map_[row + 1][col].parent_.col_ = col;
                }    
            }
        }
        //Cuarto Sucesor (Oeste)
        if (isValid(row, col - 1) == true) {
            //En caso de que la siguiente posición sea la final.
            if (isEnd(row, col - 1) == true) {
                map_[row][col - 1].parent_.row_ = row;
                map_[row][col - 1].parent_.col_ = col;
                std::cout << std::endl << "Se ha encontrado la meta." << std::endl;
                Path(speed);
                isDestination = true;
                return;
            }
            //En caso contrario.
            if ((ClosedList[row][col - 1] == false) && (isEmpty(row, col - 1) == true)) {
                cost = map_[row][col].cost_ + 1;
                if (heuristic == 1) {
                    distance = Manhattan(row, col - 1);
                } else if (heuristic == 2) {
                    distance = Euclidean(row, col - 1);
                } else if (heuristic == 3) {
                    distance = Diagonal(row, col - 1);
                } 
                function = cost + distance;
                //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                if ((map_[row][col - 1].function_ == FLT_MAX) || (map_[row][col - 1].function_ > function)) {
                    temporal.first = function;
                    temporal.second.first = row;
                    temporal.second.second = col - 1;
                    OpenList.insert(temporal);

                    map_[row][col - 1].function_ = function;
                    map_[row][col - 1].cost_ = cost;
                    map_[row][col - 1].distance_ = distance;
                    map_[row][col - 1].parent_.row_ = row;
                    map_[row][col - 1].parent_.col_ = col;
                }    
            }
        }
        if (mode == 2) {
            //Quinto Sucesor (Noreste)
            if (isValid(row - 1, col + 1) == true) {
            //En caso de que la siguiente posición sea la final.
                if (isEnd(row - 1, col + 1) == true) {
                    map_[row - 1][col + 1].parent_.row_ = row;
                    map_[row - 1][col + 1].parent_.col_ = col;
                    std::cout << std::endl << "Se ha encontrado la meta." << std::endl;
                    Path(speed);
                    isDestination = true;
                    return;
                }
                //En caso contrario.
                if ((ClosedList[row - 1][col + 1] == false) && (isEmpty(row - 1, col + 1) == true)) {
                    cost = map_[row][col].cost_ + 1.414;
                    if (heuristic == 1) {
                        distance = Manhattan(row - 1, col + 1);
                    } else if (heuristic == 2) {
                        distance = Euclidean(row - 1, col + 1);
                    } else if (heuristic == 3) {
                        distance = Diagonal(row - 1, col + 1);
                    } 
                    function = cost + distance;
                    //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                    if ((map_[row - 1][col + 1].function_ == FLT_MAX) || (map_[row - 1][col + 1].function_ > function)) {
                        temporal.first = function;
                        temporal.second.first = row - 1;
                        temporal.second.second = col + 1;
                        OpenList.insert(temporal);

                        map_[row - 1][col + 1].function_ = function;
                        map_[row - 1][col + 1].cost_ = cost;
                        map_[row - 1][col + 1].distance_ = distance;
                        map_[row - 1][col + 1].parent_.row_ = row;
                        map_[row - 1][col + 1].parent_.col_ = col;
                    }    
                }
            }
            //Sexto Sucesor (Sureste)
            if (isValid(row + 1, col + 1) == true) {
            //En caso de que la siguiente posición sea la final.
                if (isEnd(row + 1, col + 1) == true) {
                    map_[row + 1][col + 1].parent_.row_ = row;
                    map_[row + 1][col + 1].parent_.col_ = col;
                    std::cout << std::endl << "Se ha encontrado la meta." << std::endl;
                    Path(speed);
                    isDestination = true;
                    return;
                }
                //En caso contrario.
                if ((ClosedList[row + 1][col + 1] == false) && (isEmpty(row + 1, col + 1) == true)) {
                    cost = map_[row][col].cost_ + 1.414;
                    if (heuristic == 1) {
                        distance = Manhattan(row + 1, col + 1);
                    } else if (heuristic == 2) {
                        distance = Euclidean(row + 1, col + 1);
                    } else if (heuristic == 3) {
                        distance = Diagonal(row + 1, col + 1);
                    } 
                    function = cost + distance;
                    //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                    if ((map_[row + 1][col + 1].function_ == FLT_MAX) || (map_[row + 1][col + 1].function_ > function)) {
                        temporal.first = function;
                        temporal.second.first = row + 1;
                        temporal.second.second = col + 1;
                        OpenList.insert(temporal);

                        map_[row + 1][col + 1].function_ = function;
                        map_[row + 1][col + 1].cost_ = cost;
                        map_[row + 1][col + 1].distance_ = distance;
                        map_[row + 1][col + 1].parent_.row_ = row;
                        map_[row + 1][col + 1].parent_.col_ = col;
                    }    
                }
            }
            //Séptimo Sucesor (Suroeste)
            if (isValid(row + 1, col - 1) == true) {
            //En caso de que la siguiente posición sea la final.
                if (isEnd(row + 1, col - 1) == true) {
                    map_[row + 1][col - 1].parent_.row_ = row;
                    map_[row + 1][col - 1].parent_.col_ = col;
                    std::cout << std::endl << "Se ha encontrado la meta." << std::endl;
                    Path(speed);
                    isDestination = true;
                    return;
                }
                //En caso contrario.
                if ((ClosedList[row + 1][col - 1] == false) && (isEmpty(row + 1, col - 1) == true)) {
                    cost = map_[row][col].cost_ + 1.414;
                    if (heuristic == 1) {
                        distance = Manhattan(row + 1, col - 1);
                    } else if (heuristic == 2) {
                        distance = Euclidean(row + 1, col - 1);
                    } else if (heuristic == 3) {
                        distance = Diagonal(row + 1, col - 1);
                    } 
                    function = cost + distance;
                    //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                    if ((map_[row + 1][col - 1].function_ == FLT_MAX) || (map_[row + 1][col - 1].function_ > function)) {
                        temporal.first = function;
                        temporal.second.first = row + 1;
                        temporal.second.second = col - 1;
                        OpenList.insert(temporal);

                        map_[row + 1][col - 1].function_ = function;
                        map_[row + 1][col - 1].cost_ = cost;
                        map_[row + 1][col - 1].distance_ = distance;
                        map_[row + 1][col - 1].parent_.row_ = row;
                        map_[row + 1][col - 1].parent_.col_ = col;
                    }    
                }
            }
            //Octavo Sucesor (Noroeste)
            if (isValid(row - 1, col - 1) == true) {
            //En caso de que la siguiente posición sea la final.
                if (isEnd(row - 1, col - 1) == true) {
                    map_[row - 1][col - 1].parent_.row_ = row;
                    map_[row - 1][col - 1].parent_.col_ = col;
                    std::cout << std::endl << "Se ha encontrado la meta." << std::endl;
                    Path(speed);
                    isDestination = true;
                    return;
                }
                //En caso contrario.
                if ((ClosedList[row - 1][col - 1] == false) && (isEmpty(row - 1, col - 1) == true)) {
                    cost = map_[row][col].cost_ + 1.414;
                    if (heuristic == 1) {
                        distance = Manhattan(row - 1, col - 1);
                    } else if (heuristic == 2) {
                        distance = Euclidean(row - 1, col - 1);
                    } else if (heuristic == 3) {
                        distance = Diagonal(row - 1, col - 1);
                    } 
                    function = cost + distance;
                    //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                    if ((map_[row - 1][col - 1].function_ == FLT_MAX) || (map_[row - 1][col - 1].function_ > function)) {
                        temporal.first = function;
                        temporal.second.first = row - 1;
                        temporal.second.second = col - 1;
                        OpenList.insert(temporal);

                        map_[row - 1][col - 1].function_ = function;
                        map_[row - 1][col - 1].cost_ = cost;
                        map_[row - 1][col - 1].distance_ = distance;
                        map_[row - 1][col - 1].parent_.row_ = row;
                        map_[row - 1][col - 1].parent_.col_ = col;
                    }    
                }
            }
        }
    }
    if (isDestination == false) {
        std::cout << std::endl << "No se ha podido encontrar camino. " << std::endl;
    }
    return;
}

void World::Visualizer() {
    int size = 0;
    std::string output;
    std::cout << "----> Mostrando imagen del mundo simulado: " << std::endl;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (world_[i][j] == CYAN)
                size++;
            output += world_[i][j];
        }
        output.push_back('\n');  
    }
    std::cout << output << std::endl;
    std::cout << "----> El tamaño del camino es: " << size << std::endl;
}

void World::MapVisualizer() {
    std::cout << std::endl << "Imagen de las funciones: " << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (map_[i][j].function_ != FLT_MAX) {
                std::cout << "  " << map_[i][j].function_ << "  ";
            } else {
                std::cout << "  +  ";
            }
        }
        std::cout << std::endl;  
    }

    std::cout << std::endl << "Imagen de los costes: " << std::endl;
    std::cout << std::endl; 

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (map_[i][j].cost_ != FLT_MAX) {
                std::cout << "  " << map_[i][j].cost_ << "  ";
            } else {
                std::cout << "  +  ";
            }
        }
        std::cout << std::endl;  
    }

    std::cout << std::endl << "Imagen de las distancias: " << std::endl;
    std::cout << std::endl; 

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (map_[i][j].distance_ != FLT_MAX) {
                std::cout << "  " << map_[i][j].distance_ << "  ";
            } else {
                std::cout << "  +  ";
            }
        }
        std::cout << std::endl;  
    }

    std::cout << std::endl << "Imagen de los padres: " << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << " [" << map_[i][j].parent_.row_ << "][" << map_[i][j].parent_.col_ << "] ";
        }
        std::cout << std::endl;  
    }
}

void World::TaxiVisualizer() {
    std::cout << std::endl << "Datos del taxi: " << std::endl;
    std::cout << std::endl << "     Salida: [" << taxi_.start_.row_ << "][" << taxi_.start_.col_ << "]" << std::endl;
    std::cout << std::endl << "     Meta: [" << taxi_.end_.row_ << "][" << taxi_.end_.col_ << "]" << std::endl;
}