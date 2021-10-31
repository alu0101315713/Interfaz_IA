#include "world.h"

void Error() {
    std::cout << "Inserte valores dentro del rango." << std::endl;
}

int main() {
    Point start, finish;
    int rows, cols, row, col, mode, option, number, heuristic, speed, election, numberofobjects;
    char ack, character;
    bool running, done;
    float percent;

    system("clear");
    std::cout << "----> Bienvenido al Simulador de Taxi Autónomo. " << std::endl;
    std::cout << "----> Seguidamente se le mostrara la opción de crear un mapa con obstáculos y un taxi que recorra el camino óptimo entre dos puntos. " << std::endl;
    std::cout << "----> Pulse 1 y enter para continuar: ";
    std::cin >> ack;
    system("clear");

    std::cout << "----> Cree el mapa: " << std::endl;
    std::cout << "----> Introduzca el número de filas del mapa: ";
    std::cin >> rows; 
    std::cout << "----> Introduzca el número de columnas del mapa: ";
    std::cin >> cols;
    World world(rows, cols);
    world.Visualizer();
    std::cout << "----> Pulse 1 y enter para continuar: ";
    std::cin >> ack;
    system("clear");

    std::cout << "----> Introduzca las posiciones de inicio y final del camino. " << std::endl;
    std::cout << "----> Introduzca el punto inicial: " << std::endl;
    std::cout << "----> Introduzca una fila: ";
    std::cin >> row;
    std::cout << "----> Introduzca una columna: ";
    std::cin >> col;
    start.row_ = row;
    start.col_ = col;
    world.Change(row, col, RED);
    world.Visualizer();
    std::cout << "----> Pulse 1 y enter para continuar: ";
    std::cin >> ack;
    system("clear");
    std::cout << "----> Introduzca la meta: " << std::endl;
    std::cout << "----> Introduzca una fila: ";
    std::cin >> row;
    std::cout << "----> Introduzca una columna: ";
    std::cin >> col;
    finish.row_ = row;
    finish.col_ = col;
    world.Change(row, col, YELLOW);
    world.Visualizer();
    std::cout << "----> Pulse 1 y enter para continuar: ";
    std::cin >> ack;
    system("clear");    

    do {
        std::cout << "----> ¿Qué desea hacer? " << std::endl;
        std::cout << "----> 0. Leer instrucciones. " << std::endl;
        std::cout << "----> 1. Visualizar el mundo. " << std::endl;
        std::cout << "----> 2. Modificar el mundo. " << std::endl;
        std::cout << "----> 3. Comenzar el camino. " << std::endl;
        std::cout << "----> 4. Cerrar el programa. " << std::endl; 
        std::cout << "----> Introduzca su opción: ";
        std::cin >> option;
        system("clear");
        
        if (option == 0) {
            std::cout << "----> Ha seleccionado la opción de leer información sobre la aplicación. " << std::endl;
            std::ifstream readme("README.md");
            if (readme.is_open()) {
                std::cout << "----> Mostrando información sobre el programa de Taxi Autónomo. " << std::endl;
                std::cout << readme.rdbuf();
            } else {
                std::cout << "----> No dispone del fichero de instrucciones README.md. " << std::endl;
            }
            std::cout << "----> Volviendo al menú. " << std::endl;
            std::cout << "----> Pulse 1 y enter para continuar: ";
            std::cin >> ack;
            system("clear"); 
        } else if (option == 1) {
            std::cout << "----> Ha seleccionado la opción de visualizar el mundo. " << std::endl;
            world.Visualizer();
            std::cout << "----> Volviendo al menú. " << std::endl;
            std::cout << "----> Pulse 1 y enter para continuar: ";
            std::cin >> ack;
            system("clear"); 
        } else if (option == 2) {
            world.ClearPath();
            do {
                std::cout << "----> Ha seleccionado la opción de modificar el mundo. " << std::endl;
                std::cout << "----> ¿Qué desea hacer? " << std::endl;
                std::cout << "----> 1. Limpiar el mundo. " << std::endl;
                std::cout << "----> 2. Cambiar obstáculos. " << std::endl;
                std::cout << "----> 3. Cambiar posiciones de salida y meta. " << std::endl;
                std::cout << "----> 4. Volver al menú principal. " << std::endl;
                std::cout << "----> Introduzca su opción: ";
                std::cin >> election;
                system("clear");
                if (election == 1) {
                    world.Visualizer();
                    std::cout << "----> Ha seleccionado la opción de limpiar el mundo. " << std::endl;
                    std::cout << "----> Limpiando el mundo. " << std::endl;
                    world.ClearWorld();
                    world.Visualizer();
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear");
                } else if (election == 2) {
                    do {
                        world.Visualizer();
                        std::cout << "----> Ha seleccionado la opción de cambiar los obstáculos. " << std::endl;
                        std::cout << "----> ¿Qué desea hacer? " << std::endl;
                        std::cout << "----> 1. Introducir una cantidad determinada de obstáculos manualmente. " << std::endl;
                        std::cout << "----> 2. Introducir una cantidad determinada de obstáculos aleatoriamente. " << std::endl;
                        std::cout << "----> 3. Introducir un porcentaje determinado de obstáculos aleatoriamente. " << std::endl;
                        std::cout << "----> 4. Introducir obstáculos mediante un fichero. " << std::endl;
                        std::cout << "----> 5. Volver al menú de edición de mapa." << std::endl;
                        std::cout << "----> Introduzca su opción: ";
                        std::cin >> election;
                        system("clear");
                        if (election == 1) {
                            world.ClearObjects();
                            done = false;
                            std::cout << "----> Ha elegido el modo manual. " << std::endl;
                            std::cout << "----> Introduzca la cantidad de obstáculos que quiere añadir (0 para mapa limpio): " << std::endl;
                            std::cin >> number;
                            while (!done) {
                                if (number > rows * cols) {
                                    Error();
                                    std::cout << "----> Introduzca la cantidad de obstáculos que quiere añadir: " << std::endl;
                                    std::cin >> number;
                                } else {
                                    done = true;
                                }
                            }
                            for (int i = 0; i < number; i++) {
                                do {
                                    std::cout << "----> Introduzca una fila: " << std::endl;
                                    std::cin >> row;
                                    std::cout << "----> Introduzca una columna: " << std::endl;
                                    std::cin >> col;
                                    if ((!world.isEmpty(row, col)) || (world.isStart(row, col)) || (world.isEnd(row, col))) {
                                        std::cout << "----> Posicion ocupada, inserte otra distinta: " << std::endl;
                                    }
                                } while ((!world.isEmpty(row, col)) || (world.isStart(row, col)) || (world.isEnd(row, col)));
                                world.Change(row, col, WHITE);
                                world.Visualizer();
                            }
                            world.Visualizer();
                            std::cout << "----> Pulse 1 y enter para continuar: " << std::endl;
                            std::cin >> ack;
                            system("clear");
                        } else if (election == 2) {
                            world.ClearObjects();
                            done = false;
                            std::cout << "----> Ha elegido el modo automatico. " << std::endl;
                            srand(time(NULL));
                            std::cout << "----> Introduzca la cantidad de obstáculos que quiere añadir: " << std::endl;
                            std::cin >> number;
                            while (!done) {
                                if (number > rows * cols) {
                                    Error();
                                    std::cout << "----> Introduzca la cantidad de obstáculos que quiere añadir: " << std::endl;
                                    std::cin >> number;
                                } else {
                                    done = true;
                                }
                            }
                            for (int i = 0; i < number; i++) {
                                do {
                                    row = rand() % rows;
                                    col = rand() % cols;
                                } while ((!world.isEmpty(row, col)) || (world.isStart(row, col)) || (world.isEnd(row, col)));
                                world.Change(row, col, WHITE);
                            }
                            world.Visualizer();
                            std::cout << "----> Pulse 1 y enter para continuar: " << std::endl;
                            std::cin >> ack;
                            system("clear");
                        } else if (election == 3) {
                            world.ClearObjects();
                            done = false;
                            std::cout << "----> Ha elegido el modo por porcentajes. " << std::endl;
                            std::cout << "----> Introduzca el porcentaje de obstáculos que quiere añadir: " << std::endl;
                            std::cin >> percent;
                            while (!done) {
                                if ((percent > 100) || (percent < 0)) {
                                    Error();
                                    std::cout << "----> Introduzca el porcentaje de obstáculos que quiere añadir: " << std::endl;
                                    std::cin >> percent;
                                } else {
                                    done = true;
                                }
                            }
                            percent = percent / 100;
                            number = percent * (rows * cols);
                            for (int i = 0; i < number; i++) {
                                do {
                                    row = rand() % rows;
                                    col = rand() % cols;
                                } while ((!world.isEmpty(row, col)) || (world.isStart(row, col)) || (world.isEnd(row, col)));
                                world.Change(row, col, WHITE);
                            }
                            world.Visualizer();
                            std::cout << "----> Pulse 1 y enter para continuar: " << std::endl;
                            std::cin >> ack;
                            system("clear");
                        } else if (election == 4) {
                            numberofobjects = 0;
                            world.ClearObjects();
                            done = false;
                            std::cout << "----> Ha elegido el modo fichero. " << std::endl;
                            std::string filename;
                            std::cout << "----> Introduzca el fichero de entrada: ";
                            std::cin >> filename;
                            std::ifstream file(filename);
                            while (!done) {
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
                                                    file >> col;
                                                    file.get(character);
                                                    if ((character == '\n') || (file.eof())) {
                                                        if ((world.isEmpty(row, col)) && (!world.isStart(row, col)) && (!world.isEnd(row, col))) {
                                                            world.Change(row, col, WHITE);
                                                            ++numberofobjects;
                                                        }
                                                    }
                                                }
                                            } 
                                            while ((character != '\n') && !(file.eof())) {
                                                file.get(character);
                                            }   
                                        }
                                    }
                                    std::cout << "----> Fichero leido de forma exitosa." << std::endl;
                                    std::cout << "----> Se han añadido " << numberofobjects << " obstáculos. " << std::endl;
                                    done = true;
                                } else {
                                    std::cout << "----> No se ha podido abrir el fichero." << std::endl;
                                }
                            }
                        } else if (election == 5) {
                            std::cout << "----> Volviendo al menú de edición del mundo. " << std::endl;
                            std::cout << "----> Pulse 1 y enter para continuar: ";
                            std::cin >> ack;
                            system("clear");
                        } else {
                            std::cout << "----> Ha seleccionado una opción no válida. " << std::endl;
                            std::cout << "----> Volviendo al menú. " << std::endl;
                            std::cout << "----> Pulse 1 y enter para continuar: ";
                            std::cin >> ack;
                            system("clear");
                        }
                    } while (election != 5);
                    election = 2;
                } else if (election == 3) {
                    do {
                        world.Visualizer();
                        std::cout << "----> Ha seleccionado la opción de cambiar la salida y la meta. " << std::endl;
                        std::cout << "----> ¿Qué desea hacer? " << std::endl;
                        std::cout << "----> 1. Cambiar la salida. " << std::endl;
                        std::cout << "----> 2. Cambiar la meta. " << std::endl;
                        std::cout << "----> 3. Volver al menú de edición de mapa. " << std::endl;
                        std::cout << "----> Introduzca su opción: ";
                        std::cin >> election;
                        system("clear");
                        if (election == 1) {
                            world.ClearStart();
                            std::cout << "----> Introduzca el punto inicial: " << std::endl;
                            std::cout << "----> Introduzca una fila: ";
                            std::cin >> row;
                            std::cout << "----> Introduzca una columna: ";
                            std::cin >> col;
                            start.row_ = row;
                            start.col_ = col;
                            world.Change(row, col, RED);
                            world.Visualizer();
                            std::cout << "----> Pulse 1 y enter para continuar: ";
                            std::cin >> ack;
                            system("clear");
                        } else if (election == 2) {
                            world.ClearEnd();
                            std::cout << "----> Introduzca el destino: " << std::endl;
                            std::cout << "----> Introduzca una fila: ";
                            std::cin >> row;
                            std::cout << "----> Introduzca una columna: ";
                            std::cin >> col;
                            finish.row_ = row;
                            finish.col_ = col;
                            world.Change(row, col, YELLOW);
                            world.Visualizer();
                            std::cout << "----> Pulse 1 y enter para continuar: ";
                            std::cin >> ack;
                            system("clear");    
                        } else if (election == 3) {
                            std::cout << "----> Volviendo al menú de edición del mundo. " << std::endl;
                            std::cout << "----> Pulse 1 y enter para continuar: ";
                            std::cin >> ack;
                            system("clear");
                        } else {
                            std::cout << "----> Ha seleccionado una opción no válida. " << std::endl;
                            std::cout << "----> Volviendo al menú. " << std::endl;
                            std::cout << "----> Pulse 1 y enter para continuar: ";
                            std::cin >> ack;
                            system("clear");
                        }
                    } while (election != 3);
                } else if (election == 4) {
                    std::cout << "----> Volviendo al menú. " << std::endl; 
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear");
                } else {
                    std::cout << "----> Ha seleccionado una opción no válida. " << std::endl;
                    std::cout << "----> Volviendo al menú de edición de mapa. " << std::endl;
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear"); 
                }
            } while (election != 4);
            option = 2;
        } else if (option == 3) {
            do {
                std::cout << "----> Ha seleccionado el algoritmo de búsqueda. " << std::endl;
                std::cout << "----> ¿Qué desea hacer? " << std::endl;
                std::cout << "----> 1. Iniciar el algoritmo. " << std::endl;
                std::cout << "----> 2. Limpiar el camino. " << std::endl;
                std::cout << "----> 3. Volver al menú principal. " << std::endl;
                std::cout << "----> Introduzca su opción: ";
                std::cin >> election;
                system("clear");
                if (election == 1) {
                    do {
                        world.ClearPath();
                        std::cout << "----> ¿Qué tipo de taxi prefiere? " << std::endl;
                        std::cout << "----> 1. 4 direcciones." << std::endl;
                        std::cout << "----> 2. 8 direcciones. " << std::endl;
                        std::cout << "----> Introduzca su opción: ";
                        std::cin >> option;
                        if ((option != 1) && (option != 2)) {
                            Error();
                        }
                        system("clear");
                    } while ((option != 1) && (option != 2));
                    do {
                        std::cout << "----> ¿Qué tipo de heurística prefiere? " << std::endl;
                        std::cout << "----> 1. Manhattan." << std::endl;
                        std::cout << "----> 2. Euclídea. " << std::endl;
                        std::cout << "----> 3. Diagonal. " << std::endl; 
                        std::cout << "----> Introduzca su opción: ";
                        std::cin >> heuristic;
                        if ((heuristic != 1) && (heuristic != 2) && (heuristic != 3)) {
                            Error();
                        }
                        system("clear");
                    } while ((heuristic != 1) && (heuristic != 2) && (heuristic != 3));
                    do {
                        std::cout << "----> ¿Qué velocidad de ejecución quiere? (Entre 1-60 fps)" << std::endl; 
                        std::cout << "----> Introduzca su opción: ";
                        std::cin >> speed;
                        if ((speed < 1) || (speed > 60)) {
                            Error();
                        }
                        system("clear");
                    } while ((speed < 1) || (speed > 60));
                    auto start = std::chrono::high_resolution_clock::now();
                    world.AStar(option, heuristic, speed);
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                    std::cout << std::endl << "----> La duración del algoritmo ha sido de: " << duration.count() << " microsegundos." << std::endl << std::endl;
                } else if (election == 2) {
                    std::cout << "----> Limpiando el camino. " << std::endl; 
                    world.ClearPath();
                    world.Visualizer();
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear");
                } else if (election == 3) {
                    std::cout << "----> Volviendo al menú. " << std::endl; 
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear");
                } else {
                    std::cout << "----> Ha seleccionado una opción no válida. " << std::endl;
                    std::cout << "----> Volviendo al menú de algoritmo de búsqueda. " << std::endl;
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear"); 
                }
            } while (election != 3);
        } else if (option = 4) {
            do {
                std::cout << "----> Ha seleccionado la opción de cerrar el programa. " << std::endl;
                std::cout << "----> ¿Seguro que desea cerrar el programa?" << std::endl;
                std::cout << "----> 1. Cerrar el programa. " << std::endl;
                std::cout << "----> 2. Volver al menú principal. " << std::endl;
                std::cout << "----> Introduzca su opción: ";
                std::cin >> election;
                system("clear");
                if (election == 1) {
                    std::cout << "----> Gracias por usar el programa de taxi autónomo. " << std::endl;
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear");
                    exit(1);
                } else if (election == 2) {
                    std::cout << "----> Volviendo al menú. " << std::endl; 
                    option = 1;
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear");
                } else {
                    std::cout << "----> Ha seleccionado una opción no válida. " << std::endl;
                    std::cout << "----> Volviendo al menú de cierre del programa. " << std::endl;
                    std::cout << "----> Pulse 1 y enter para continuar: ";
                    std::cin >> ack;
                    system("clear");
                }
            } while ((election < 1) || (election > 2));
    
        } else {
            std::cout << "----> Ha seleccionado una opción no válida. " << std::endl;
            std::cout << "----> Volviendo al menú. " << std::endl;
            std::cout << "----> Pulse 1 y enter para continuar: ";
            std::cin >> ack;
            system("clear"); 
        }
    } while (option != 4);
    return 0;
}