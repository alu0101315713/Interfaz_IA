#include "world.h"

//Función que termina la ejecución si se da un error de gravedad.
void WorldError() {
    std::cout << "Inserte valores dentro del rango." << std::endl;
    exit(1);
}

//En los constructores creamos el mundo.
World::World() {
    rows_ = 20;
    cols_ = 35;
    std::vector<std::string> aux;
    std::vector<Node> aux_map;
    aux.resize(cols_);
    aux_map.resize(cols_);
    for (int i = 0; i < cols_; i++) {
        aux[i] = "  ";
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
        aux[i] = "  ";
    }
    for (int i = 0; i < rows_; i++) {
        world_.push_back(aux);
        map_.push_back(aux_map);
    }
}

//Destruimos el mundo.
World::~World() {
    world_.clear();
    map_.clear();
}

//Comprueba si una posición está dentro de los límites del mundo.
bool World::isValid(int row, int col) {
    return ((row >= 0) && (row < rows_) && (col >= 0) && (col < cols_));
}

//Comprueba si una posición está vacía. Es decir, que no la ocupa un obstáculo.
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

//Comprueba si una posición es el inicio del camino.
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

//Comprueba si una posición es el final del camino.
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

//Cambia una casilla de color. En caso de ser roja, es la salida y en caso de ser amarilla es la meta.
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

//Limpia el contenido del mundo.
void World::ClearWorld() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            world_[i][j] = "  ";
        } 
    }
    taxi_.start_.row_ = 0;
    taxi_.start_.col_ = 0;
    taxi_.end_.row_ = 0;
    taxi_.end_.col_ = 0;
}

//Limpia los objetos del mundo.
void World::ClearObjects() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (world_[i][j] == WHITE)
                world_[i][j] = "  ";
        } 
    }
}

//Limpia el inicio del camino.
void World::ClearStart() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (world_[i][j] == RED)
                world_[i][j] = "  ";
        } 
    }
    taxi_.start_.row_ = 0;
    taxi_.start_.col_ = 0;
}

//Limpia el final del camino.
void World::ClearEnd() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (world_[i][j] == YELLOW)
                world_[i][j] = "  ";
        } 
    }
    taxi_.end_.row_ = 0;
    taxi_.end_.col_ = 0;
}

//Limpia el camino.
void World::ClearPath() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if ((world_[i][j] == GREEN) || (world_[i][j] == BLUE))
                world_[i][j] = "  ";
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

//Función que dibuja el camino.
void World::Path(int speed) {
    std::chrono::_V2::system_clock::time_point time;
    int timeint = speed;
    float cost = 0;
    std::cout << std::endl << "----> El camino es el siguiente: " << std::endl;
    std::stack<Point> Path;
    Point destination, temporal;

    destination.row_ = taxi_.end_.row_;
    destination.col_ = taxi_.end_.col_;

    //Busca hasta que la posición del padre sea la misma que la propia posición del nodo. Es decir, hasta encontrar al primer nodo del camino.
    while (!((map_[destination.row_][destination.col_].parent_.row_ == destination.row_) && (map_[destination.row_][destination.col_].parent_.col_ == destination.col_))) {
        //Insertamos en la pila el último nodo sin insertar del camino y actualizamos datos.
        Path.push(destination);
        temporal.row_ = map_[destination.row_][destination.col_].parent_.row_;
        temporal.col_ = map_[destination.row_][destination.col_].parent_.col_;
        destination.row_ = temporal.row_;
        destination.col_ = temporal.col_;
    }
    temporal.row_ = taxi_.start_.row_;
    temporal.col_ = taxi_.start_.col_;

    Path.push(destination);
    //Empieza a cambiar de color los nodos del camino desde el inicio al final.
    while (!Path.empty()) {
        time = std::chrono::system_clock::now();
        std::cout << "----> El tamaño del camino es: " << map_[temporal.row_][temporal.col_].cost_ << std::endl;
        cost = map_[temporal.row_][temporal.col_].cost_;
        temporal.row_ = Path.top().row_;
        temporal.col_ = Path.top().col_;
        Path.pop();
        //Busca el nodo analizado.
        for (int i = 0; i < world_.size(); i++) {
            for (int j = 0; j < world_[i].size(); j++) {
                if ((world_[i][j] != RED) && (world_[i][j] != YELLOW) && (world_[i][j] != GREEN)) {
                    if (map_[i][j].function_ != FLT_MAX)
                        world_[i][j] = BLUE;
                    if ((temporal.row_ == i) && (temporal.col_ == j)) 
                        world_[i][j] = GREEN;
                }
            } 
        }
        time += std::chrono::milliseconds(1000 / timeint);
        std::this_thread::sleep_until(time);
        system("clear");
        Visualizer();
    }
    std::cout << "----> La longitud del camino es de: " << cost << " unidades." << std::endl;
    return;
}

void World::AStar(int mode, int heuristic, int speed, int algorithm) {
    //Será verdadero cuando se encuentre la meta.
    bool isDestination = false;
    float cost, distance, function;
    int numberofneighbours;
    if (mode == 1) {
        numberofneighbours = 4;
    } else if (mode  == 2) {
        numberofneighbours = 8;
    }
    //Comprobamos si estamos en la meta.
    if (isEnd(taxi_.start_.row_, taxi_.start_.col_) == true) {
        std::cout << std::endl << "----> Nos encontramos en la meta. " << std::endl;
        isDestination = true;
        return;
    }
    //Lista cerrada inicializada a falso, ya que ningún nodo ha sido incluido.
    bool ClosedList[rows_][cols_];
    memset(ClosedList, false, sizeof(ClosedList));

    int row, col;
    
    //Inicializamos todos los nodos con valores predeterminados.
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

    //Sucesores del nodo actual.
    std::pair<int, int> neighbours[8];

    //Mientras la lista no esté vacía, se seguirá ejecutando.
    while (OpenList.empty() == false) { 
        begin = *OpenList.begin();
        OpenList.erase(OpenList.begin());

        row = begin.second.first;
        col = begin.second.second;
        ClosedList[row][col] = true;

        //Preparamos los sucesores.
        neighbours[0].first = row - 1;
        neighbours[0].second = col;
        neighbours[1].first = row;
        neighbours[1].second = col + 1;
        neighbours[2].first = row + 1;
        neighbours[2].second = col;
        neighbours[3].first = row;
        neighbours[3].second = col - 1;
        neighbours[4].first = row - 1;
        neighbours[4].second = col + 1;
        neighbours[5].first = row + 1;
        neighbours[5].second = col + 1;
        neighbours[6].first = row + 1;
        neighbours[6].second = col - 1;
        neighbours[7].first = row - 1;
        neighbours[7].second = col - 1;

        for (int i = 0; i < numberofneighbours; i++) {
            if (isValid(neighbours[i].first, neighbours[i].second) == true) {
                //En caso de que la siguiente posición sea la final.
                if (isEnd(neighbours[i].first, neighbours[i].second) == true) {
                    map_[neighbours[i].first][neighbours[i].second].parent_.row_ = row;
                    map_[neighbours[i].first][neighbours[i].second].parent_.col_ = col;
                    std::cout << std::endl << "----> Se ha encontrado la meta." << std::endl;
                    Path(speed);
                    isDestination = true;
                    return;
                }
                //En caso contrario.
                if ((ClosedList[neighbours[i].first][neighbours[i].second] == false) && (isEmpty(neighbours[i].first, neighbours[i].second) == true)) {
                    if (i < 4) {
                        cost = map_[row][col].cost_ + 1;
                    } else if (i >= 4) {
                        cost = map_[row][col].cost_ + 1.414;
                    }
                    if (algorithm == 1) {
                        if (heuristic == 1) {
                            distance = Manhattan(neighbours[i].first, neighbours[i].second);
                        } else if (heuristic == 2) {
                            distance = Euclidean(neighbours[i].first, neighbours[i].second);
                        } else if (heuristic == 3) {
                            distance = Diagonal(neighbours[i].first, neighbours[i].second);
                        } 
                    } else if (algorithm == 2) {
                        distance = 0;
                    }
                    function = cost + distance;
                    //Añadirlo a la lista abierta si no lo está o actualizar un valor por otro mejor en caso de que lo esté.
                    if ((map_[neighbours[i].first][neighbours[i].second].function_ == FLT_MAX) || (map_[neighbours[i].first][neighbours[i].second].function_ > function)) {
                        temporal.first = function;
                        temporal.second.first = neighbours[i].first;
                        temporal.second.second = neighbours[i].second;
                        OpenList.insert(temporal);

                        map_[neighbours[i].first][neighbours[i].second].function_ = function;
                        map_[neighbours[i].first][neighbours[i].second].cost_ = cost;
                        map_[neighbours[i].first][neighbours[i].second].distance_ = distance;
                        map_[neighbours[i].first][neighbours[i].second].parent_.row_ = row;
                        map_[neighbours[i].first][neighbours[i].second].parent_.col_ = col;
                    }    
                }
            }
        }
    }
    if (isDestination == false) {
        std::cout << std::endl << "----> No se ha podido encontrar camino. " << std::endl;
    }
    return;
}

void World::Visualizer() {
    int size = 0, expand = 0;
    std::string output;
    std::cout << "----> Mostrando imagen del mundo simulado: " << std::endl;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (world_[i][j] == GREEN)
                size++;
            if (world_[i][j] == BLUE)
                expand++;
            output += world_[i][j];
        }
        output.push_back('\n');  
    }
    std::cout << output << std::endl;
    std::cout << "----> El número de nodos del camino es: " << size << std::endl << std::endl;
    std::cout << "----> El número de nodos expandidos es: " << size + expand << std::endl << std::endl;
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