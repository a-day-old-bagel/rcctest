#include <iostream>
//#include "RuntimeObjectSystem.h"

int main(int argc, char **argv) {
  char input;
  do {
    std::cout << "enter char:" << std::endl;
    std::cin >> input;
  } while (input != 'q');
  return 0;
}
