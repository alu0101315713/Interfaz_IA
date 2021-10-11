#include "world.h"

void Error() {
    std::cout << "Inserte valores dentro del rango." << std::endl;
    exit(1);
}

int main() {
    int x, xSize, y, ySize, xLimit, yLimit, mode, number;
    std::cout << "Introduzca una dimension para el eje de las X: " << std::endl;
    std::cin >> x; 
    std::cout << "Introduzca una dimension para el eje de las Y: " << std::endl;
    std::cin >> y;
    xSize = x;
    ySize = y;
    xLimit = x - 1;
    yLimit = y - 1;
    World world(x, y);
    world.Visualizer();
    std::cout << "Desea rellenar el mapa de forma manual o automatica? " << std::endl << "1. Manual - 2.Automatica " << std::endl; 
    std::cin >> mode;
    if ((mode != 1) && (mode != 2)) {
        Error();
    } else if (mode == 1) {
        std::cout << "Introduzca la cantidad de obstáculos que quiere añadir: " << std::endl;
        std::cin >> number;
        if (number > xSize*ySize)
            Error();
        for (int i = 0; i < number; i++) {
            std::cout << "Introduzca una posicion en el eje de las X: " << std::endl;
            std::cin >> x;
            std::cout << "Introduzca una posicion en el eje de las Y: " << std::endl;
            std::cin >> y;
            world.Change(x, y);
            world.Visualizer();
        }
        world.Visualizer();
    } else if (mode == 2) {
        srand(time(NULL));
        std::cout << "Introduzca la cantidad de obstáculos que quiere añadir: " << std::endl;
        std::cin >> number;
        if (number > xSize*ySize)
            Error();
        for (int i = 0; i < number; i++) {
            x = rand() % xLimit;
            y = rand() % yLimit;
            world.Change(x, y);
        }
        world.Visualizer();
    }
    std::cout << "Introduzca la salida: " << std::endl;
    std::cout << "Introduzca una posicion en el eje de las X: " << std::endl;
    std::cin >> x;
    std::cout << "Introduzca una posicion en el eje de las Y: " << std::endl;
    std::cin >> y;
    world.Set(x, y, 'S');
    world.Visualizer();
    std::cout << "Introduzca la meta: " << std::endl;
    std::cout << "Introduzca una posicion en el eje de las X: " << std::endl;
    std::cin >> x;
    std::cout << "Introduzca una posicion en el eje de las Y: " << std::endl;
    std::cin >> y;
    world.Set(x, y, 'F');
    world.Visualizer();
    return 0;
}