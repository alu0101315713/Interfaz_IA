#include "funcions.h"

/*
#include "functions.cc"
#include "taxi.cc"
#include "world.cc"
*/





int main (void) {
  unsigned rows, columns, taxi_row, taxi_column, row, column;
  unsigned option = 0;
  bool stop;
  std::string filename;
  char second_option;
  std::cout << "\nEste simulador permite mover un taxi de un punto a otro en un";
  std::cout << " mapa rectangular.\n\nPara empezar, introduce las dimensiones d";
  std::cout << "e la matriz que formará el mapa.\n";
  GetMapSize(rows, columns);
  World world(rows, columns);
  std::cout << "\nFija la posición inicial del taxi." << std::endl;
  Taxi taxi(taxi_row, taxi_column);
  GetPosition(taxi_row, taxi_column, world, taxi);
  taxi.Travel(taxi_row, taxi_column);


  world.SetDirection(3, 3, 'v');
  world.SetDirection(4, 3, 'v');
  world.SetDirection(5, 3, '>');
  world.SetDirection(5, 4, '>');
  world.SetDirection(5, 5, '>');
  world.SetDirection(5, 6, '^');
  world.SetDirection(4, 6, '#');


  DisplayObstacleMenu();
  ChooseObstacleOption(option);
  switch (option) {
    case 1:

      break;
    case 2:

      break;
    case 3:
        std::cout << "Introduce el nombre del fichero de datos: ";
        std::cin >> filename;
        world.ReadObstaclesFromFile(filename, taxi);
        
      break;
    case 4:

      break;
    case 5:

      break;
    default:
      break;
  }







  
  while (option != 5) {
    DisplayMainMenu();
    ChooseMainOption(option);
    switch (option) {
      case 1:
        stop = false;
        while (!stop) {
          GetPosition(row, column, world, taxi);
          world.SetObstacle(row, column, taxi);
          std::cout << "Pulsa la tecla '1' para añadir otro obstáculo, o puls";
          std::cout << "a otra para volver al menú: ";
          std::cin >> second_option;
          if (second_option != '1') {
            stop = true;
          }
        }
        break;
      case 2:
        
        break;
      case 3:
        std::cout << std::endl;
        world.PrintWorld(taxi);
        break;
      case 5:
        std::cout << "Se va a cerrar el programa." << std::endl;
        break;
      default:
        break;
    }
  }
}