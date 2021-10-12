#include "funcions.h"

/*
#include "functions.cc"
#include "taxi.cc"
#include "world.cc"
*/

void Error() {
    std::cout << "Inserte valores dentro del rango." << std::endl;
    exit(1);
}

int main (void) {
  unsigned rows, columns, taxi_row, taxi_column, row, column, number, x, y;
  float percent;
  unsigned option = 0;
  bool stop, done;
  done = true;
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

  /*world.SetDirection(3, 3, 'v');
  world.SetDirection(4, 3, 'v');
  world.SetDirection(5, 3, '>');
  world.SetDirection(5, 4, '>');
  world.SetDirection(5, 5, '>');
  world.SetDirection(5, 6, '^');
  world.SetDirection(4, 6, '#');*/

  DisplayObstacleMenu();
  ChooseOption(option);
  switch (option) {
    case 1:
      std::cout << "Introduzca la cantidad de obstáculos que quiere añadir: " << std::endl;
      std::cin >> number;
      if (number > world.GetRows() * world.GetColumns())
        Error();
      for (int i = 0; i <= number; i++) {
        while (!done) {
          std::cout << "Introduzca una fila: " << std::endl;
          std::cin >> x;
          std::cout << "Introduzca una columna: " << std::endl;
          std::cin >> y;
          if (world.CheckPosition(x, y, taxi)) {
            world.SetObstacle(x, y, taxi);
            done = true;
          } else {
            std::cout << "Introduzca otra posición, puesto que esa está ocupada." << std::endl; 
          }
        }
        done = false;
        world.PrintWorld(taxi);
      }
      break;
    case 2:
      srand(time(NULL));
      std::cout << "Introduzca la cantidad de obstáculos que quiere añadir: " << std::endl;
      std::cin >> number;
      if (number > world.GetRows() * world.GetColumns())
        Error();
      for (int i = 0; i <= number; i++) {
        while (!done) {
          x = rand() % world.GetColumns() - 1;
          y = rand() % world.GetRows() - 1;
          if (world.CheckPosition(x, y, taxi)) {
            world.SetObstacle(x, y, taxi);
            done = true;
          }
        }
        done = false;
      }
      world.PrintWorld(taxi);
      break;
    case 3:
      std::cout << "Introduce el nombre del fichero de datos: ";
      std::cin >> filename;
      world.ReadObstaclesFromFile(filename, taxi);   
      break;
    case 4:
      srand(time(NULL));
      std::cout << "Introduzca el porcentaje de obstáculos que quiere añadir: " << std::endl;
      std::cin >> percent;
      if ((percent > 100) || (percent < 0))
        Error();
      percent = percent / 100;
      number = percent * (world.GetRows() * world.GetColumns());
      for (int i = 0; i <= number; i++) {
        while (!done) {
          x = rand() % world.GetColumns() - 1;
          y = rand() % world.GetRows() - 1;
          if (world.CheckPosition(x, y, taxi)) {
            world.SetObstacle(x, y, taxi);
            done = true;
          }
        }
        done = false;
      }
      world.PrintWorld(taxi);
      break;
    default:
      break;
  }
  option = 5;
  while (option != 4) {
    DisplayMainMenu();
    ChooseOption(option);
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
      case 4:
        std::cout << "Se va a cerrar el programa." << std::endl;
        break;
      default:
        break;
    }
  }
}