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
      } catch (std::out_of_range& excepcion) {
        std::cout << "El número introducido es demasiado grande." << std::endl;
      }
    }
    if (!positive) {
      if (include_zero) {
        std::cout << "Introduce un número mayor o igual a 0: ";
      } else {
        std::cout << "Introduce un número positivo: ";
      }
    }
  }
  return result;
}



void
GetMapSize(unsigned& rows, unsigned& columns) {
  std::cout << "Introduce el número de filas del mapa: ";
  rows = EnterNonNegativeNumber(false);
  std::cout << "Introduce el número de columnas del mapa: ";
  columns = EnterNonNegativeNumber(false);  
}



void GetPosition(unsigned& row, unsigned& column, World& world, Taxi& taxi) {
  bool correct = false;
  while (!correct) {
    std::cout << "Introduce la fila: ";
    row = EnterNonNegativeNumber(true);  
    std::cout << "Introduce la columna: ";
    column = EnterNonNegativeNumber(true);    
    if (world.CheckPosition(row, column, taxi)) {
      correct = true;
    } else {
      std::cout << "Posición no aceptada. Elige otra." << std::endl;
    }
  
  
/*  
  bool correct = false;
  while (!correct) {
    std::cout << "Introduce la fila: ";
    row = EnterNonNegativeNumber(true);
    if (row < max_rows) {
      correct = true;
    } else {
      std::cout << "La fila introducida no existe. Elige una menor." << std::endl;
    }
  }
  correct = false;
  while (!correct) {
    std::cout << "Introduce la columna: ";
    column = EnterNonNegativeNumber(true);
    if (column < max_columns) {
      correct = true;
    } else {
      std::cout << "La columna introducida no existe. Elige una menor." << std::endl;
    }
  */
  }
}



void DisplayObstacleMenu() {
  std::cout << "\n¿Cómo quieres introducir los obstáculos?" << std::endl;
  std::cout << "1: Añadir obstáculos uno a uno" << std::endl;
  std::cout << "2: Introducir un porcentaje" << std::endl;
  std::cout << "3: Leer obstáculos de fichero" << std::endl;
  std::cout << "4: No añadir obstáculos" << std::endl << std::endl;
}



void ChooseObstacleOption(unsigned& option) {
  bool correct_option = false;
  while (!correct_option) {
    std::cout << "Elige una opción: ";
    option = EnterNonNegativeNumber(false);
    if ((option >= 1) && (option <= 4)) {
      correct_option = true;
    } else {
      std::cout << "Opción no contemplada. Elige otra." << std::endl;
    }
  }
}




void DisplayMainMenu() {
  std::cout << "\nElige una de las siguientes opciones:" << std::endl;
  std::cout << "1: Añadir / eliminar obstáculos" << std::endl;
  std::cout << "2: Desplazar el taxi" << std::endl;
  std::cout << "3: Visualizar el mundo" << std::endl;  
  std::cout << "4: Crear un nuevo mundo" << std::endl;  
  std::cout << "5: Cerrar el programa" << std::endl << std::endl;
}



void ChooseMainOption(unsigned& option) {
  bool correct_option = false;
  while (!correct_option) {
    std::cout << "Elige una opción: ";
    option = EnterNonNegativeNumber(false);
    if ((option >= 1) && (option <= 5)) {
      correct_option = true;
    } else {
      std::cout << "Opción no contemplada. Elige otra." << std::endl;
    }
  }
}