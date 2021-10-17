#include "funcions.h"

/*
#include "functions.cc"
#include "taxi.cc"
#include "world.cc"
*/




int main (void) {
  unsigned rows, columns, initial_row, initial_column, final_row, final_column, row, column, number, x, y, added_obstacles, erased_obstacles, second_option;
  float percent;
  unsigned option = 0;
  bool stop, done;
  done = true;
  std::string filename;
  std::cout << "\nEste simulador permite mover un taxi de un punto a otro en un ";
  std::cout << "mapa rectangular.\n\nPara empezar, introduzca las dimensiones de ";
  std::cout << "la matriz que formará el mapa.\n";
  GetMapSize(rows, columns);
  World world(rows, columns);
  std::cout << "\nFije la posición inicial del taxi." << std::endl;
  GetPosition(initial_row, initial_column, world);
  std::cout << "\nFije la posición final del taxi." << std::endl;
  GetPosition(final_row, final_column, world);

  Taxi taxi(initial_row, initial_column, final_row, final_column, world);

  AddObstacles(world, taxi);

  option = 5;
  while (option != 4) {
    DisplayMainMenu();
    ChooseOption(option, 1, 4);
    std::cout << std::endl;
    switch (option) {
      case 1:
          std::cout << "¿Desea añadir o eliminar obstáculos?" << std::endl;
          std::cout << "[1] Añadir obstáculos" << std::endl;
          std::cout << "[2] Eliminar obstáculos" << std::endl;
          ChooseOption(second_option, 1, 2);
          if (second_option == 1) {
            AddObstacles(world, taxi);
          } else {
            stop = false;
            erased_obstacles = 0;
            while (!stop) {
              done = false;
              while (!done) {
                std::cout << "Introduzca la fila del obstáculo a eliminar: ";
                x = EnterNonNegativeNumber(true);
                std::cout << "Introduzca la columna del obstáculo a eliminar: ";
                y = EnterNonNegativeNumber(true);
                if (!world.CheckPosition(x, y, taxi)) {
                  world.EraseObstacle(x, y);
                  done = true;
                  ++erased_obstacles;
                  world.PrintWorld(taxi);
                } else {
                  std::cout << std::endl << "No hay ningún obstáculo en esa casilla." << std::endl; 
                }
              }
              std::cout << "¿Desea eliminar otro obstáculo?" << std::endl;
              std::cout << "[1] Sí" << std::endl;
              std::cout << "[2] No" << std::endl;
              ChooseOption(second_option, 1, 2);
              if (second_option == 2) {
                std::cout << "Se han eliminado " << erased_obstacles << " obstáculos." << std::endl;
                stop = true;
              }
            }
          }
        break;
      case 2:
        std::cout << "Coordenadas actuales del taxi: (" << taxi.GetRow() << ", " << taxi.GetColumn() << ")\n";
        std::cout << "Coordenadas actuales del destino: (" << taxi.GetRow() << ", " << taxi.GetColumn() << ")\n";
        std::cout << "¿Desea realizar el viaje hasta el destino actual, o prefiere cambiarlo?";
        std::cout << "[1] Viajar hasta el destino actual" << std::endl;
        std::cout << "[2] Elegir un nuevo destino y viajar hasta él" << std::endl;
        ChooseOption(second_option, 1, 2);
        if (second_option == 2) {
          std::cout << "\nFije la posición final del taxi." << std::endl;
          GetPosition(final_row, final_column, world);
        }
        std::cout << "¿El taxi se podrá mover en 4 o en 8 direcciones?";
        std::cout << "[1] 4 direcciones" << std::endl;
        std::cout << "[2] 8 direcciones" << std::endl;
        ChooseOption(second_option, 1, 2);
        if (second_option == 1) {
          taxi.SetMovementMode(false);
        } else {
          taxi.SetMovementMode(true);
        }

        /* ALGORITMO */
        
        break;
      case 3:
        world.PrintWorld(taxi);
        break;
      case 4:
        std::cout << "Se va a cerrar el programa." << std::endl << std::endl;
        break;
      default:
        break;
    }
  }
}