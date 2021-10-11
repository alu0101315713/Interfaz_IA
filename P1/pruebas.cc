#include <iostream>
#include <string>
#include <fstream>

int main (void) {
  int n1, n2;
  std::ifstream file("prueba.txt");
  while (!file.eof()) {
    file >> n1 >> n2;
    std::cout << n1 << " " << n2 << std::endl;
  }


}