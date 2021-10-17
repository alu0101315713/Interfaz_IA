#include "funcions.h"



void GetObstacles() {

}



bool 
IsStringNumber(std::string& string) {
  if ((string[0] == '-') && (string.length() == 1)) {
    return false;
  }
  for (int character = 0; character < string.length(); ++character) {
    if (((character == 0) && (string[character] != '-') && 
        (!isdigit(string[character]))) || ((!isdigit(string[character])) 
        && (character != 0))) {
      return false;
    }
  }
  return true;
}



unsigned
EnterNonNegativeNumber(bool include_zero) {
  unsigned result;
  std::string aux;
  bool positive = false;
  while (!positive) {
    std::cin >> aux;
    if ((aux[0] != '-') && IsStringNumber(aux)) {
      try {
        result = stoul(aux);
        if ((!include_zero) && (result == 0)) {
          positive = false;
        } else {
          positive = true;
        }
      } catch (std::out_of_range& exception) {
        std::cout << "El número introducido es demasiado grande." << std::endl;
      }
    }
    if (!positive) {
      if (include_zero) {
        std::cout << "Introduzca un número mayor o igual a 0: ";
      } else {
        std::cout << "Introduzca un número positivo: ";
      }
    }
  }
  return result;
}



float
EnterNonNegativeFloat(bool include_zero) {
  std::string input;
  bool positive = false;
  bool float_entered;
  float result;
  while (!positive) {
    float_entered = false;
    while (!float_entered) {
      std::cin >> input;
      try {
        result = stoi(input);
        result = stof(input);
        if (((!include_zero) && (result == 0)) || (result < 0)) {
          positive = false;
        } else {
          positive = true;
        }
        float_entered = true;
      } catch (std::invalid_argument& exception) {
        std::cout << "Introduzca un número, entero o decimal: ";
      } catch (std::out_of_range& exception) {
        std::cout << "Rango permitido: de -340282346638528859811704183484516925440.0 a 340282346638528859811704183484516925440.0.\n";
        std::cout << "Introduzca un número en ese rango: ";
      }
    }
    if (!positive) {
      if (include_zero) {
        std::cout << "Introduzca un número mayor o igual a 0: ";
      } else {
        std::cout << "Introduzca un número positivo: ";
      }
    }
  }
  return result;
}


void
GetMapSize(unsigned& rows, unsigned& columns) {
  std::cout << "Introduzca el número de filas del mapa: ";
  rows = EnterNonNegativeNumber(false);
  std::cout << "Introduzca el número de columnas del mapa: ";
  columns = EnterNonNegativeNumber(false);  
}



void 
GetPosition(unsigned& row, unsigned& column, World& world) {
  bool correct = false;
  while (!correct) {
    std::cout << "Introduzca la fila: ";
    row = EnterNonNegativeNumber(true);  
    std::cout << "Introduzca la columna: ";
    column = EnterNonNegativeNumber(true);    
    if (world.CheckIfInBounds(row, column) && world.CheckEmpty(row, column)) {
      correct = true;
    } else {
      std::cout << "Posición no aceptada. Elija otra." << std::endl;
    }
  }
}



void 
DisplayObstacleMenu() {
  std::cout << "\n¿Cómo quiere introducir los obstáculos?" << std::endl;
  std::cout << "1: Añadir obstáculos uno a uno (Seleccione 0 para generar un mapa limpio)" << std::endl;
  std::cout << "2: Introducir una cantidad fija de obstáculos en posiciones aleatorias" << std::endl;
  std::cout << "3: Leer obstáculos de un fichero" << std::endl;
  std::cout << "4: Llenar un porcentaje de las celdas del mapa con obstáculos" << std::endl;
}



void 
ChooseOption(unsigned& option, int minimum, int maximum) {
  bool correct_option = false;
  while (!correct_option) {
    std::cout << "Elija una opción: ";
    option = EnterNonNegativeNumber(false);
    if ((option >= minimum) && (option <= maximum)) {
      correct_option = true;
    } else {
      std::cout << "Opción no contemplada. Elija otra." << std::endl;
    }
  }
}



void 
DisplayMainMenu() {
  std::cout << "\nElija una de las siguientes opciones:" << std::endl;
  std::cout << "1: Añadir / eliminar obstáculos" << std::endl;
  std::cout << "2: Seleccionar un destino y desplazar el taxi hasta él" << std::endl;
  std::cout << "3: Visualizar el mundo" << std::endl;   
  std::cout << "4: Cerrar el programa" << std::endl << std::endl;
}



void 
AddObstacles(World& world, Taxi& taxi) {
  unsigned option, added_obstacles, number, x, y;
  float percent;
  bool done;
  bool correct_input = false;
  std::string filename;
  DisplayObstacleMenu();
  ChooseOption(option, 1, 4);
  added_obstacles = 0;
  switch (option) {
    case 1:
      std::cout << "Introduzca la cantidad de obstáculos que quiere añadir: ";
      while (!correct_input) {
        number = EnterNonNegativeNumber(true);
        if (number > world.GetRows() * world.GetColumns()) {
          std::cout << "El mundo actual no tiene tantas casillas. Introduzca otro número: ";
        } else {
          correct_input = true;
        }
      }
      for (int i = 0; i < number; i++) {
        done = false;
        if (world.GetFreeCells() == 0) {
          std::cout << "No se pueden añadir más obstáculos." << std::endl;
          continue; 
        }
        while (!done) {
          std::cout << "Introduzca una fila: ";
          x = EnterNonNegativeNumber(true);
          std::cout << "Introduzca una columna: ";
          y = EnterNonNegativeNumber(true);
          if (world.CheckPosition(x, y, taxi)) {
            world.SetObstacle(x, y, taxi);
            done = true;
            ++added_obstacles;
            world.PrintWorld(taxi);
          } else {
            std::cout << "\nIntroduzca otra posición, puesto que esa está ocupada.\n" << std::endl; 
          }
        }
      }
      break;
    case 2:
      srand(time(NULL));
      std::cout << "Introduzca la cantidad de obstáculos que quiere añadir: ";
      while (!correct_input) {
        number = EnterNonNegativeNumber(true);
        if (number > world.GetRows() * world.GetColumns()) {
          std::cout << "El mundo actual no tiene tantas casillas. Introduzca otro número: ";
        } else {
          correct_input = true;
        }
      }
      for (int i = 0; i < number; i++) {
        if (world.GetFreeCells() == 0) {
          continue;
        }
        done = false;
        while (!done) {
          x = rand() % world.GetRows();
          y = rand() % world.GetColumns();
          if (world.CheckPosition(x, y, taxi)) {
            world.SetObstacle(x, y, taxi);
            done = true;
            ++added_obstacles;
          }
        }
      }
      break;
    case 3:
      std::cout << "Introduce el nombre del fichero de datos: ";
      std::cin >> filename;
      world.ReadObstaclesFromFile(filename, taxi, added_obstacles);   
      break;
    case 4:
      srand(time(NULL));
      std::cout << "Introduzca el porcentaje de obstáculos que quiere añadir: ";
      while (!correct_input) {
        percent = EnterNonNegativeFloat(true);
        if ((percent >= 100) || (percent <= 0)) {
          std::cout << "Introduzca un porcentaje entre el 0% y el 100% (no incluidos): ";
        } else {
          correct_input = true;
        }
      }
      percent = percent / 100;
      number = percent * (world.GetRows() * world.GetColumns());
      for (int i = 0; i < number; i++) {
        if (world.GetFreeCells() == 0) {
          continue;
        }
        done = false;
        while (!done) {
          x = rand() % world.GetRows();
          y = rand() % world.GetColumns();
          if (world.CheckPosition(x, y, taxi)) {
            world.SetObstacle(x, y, taxi);
            done = true;
            ++added_obstacles;
          }
        }
      }
      break;
    default:
      break;
  }
  world.PrintWorld(taxi);
  std::cout << "Se han añadido " << added_obstacles << " obstáculos." << std::endl;
}