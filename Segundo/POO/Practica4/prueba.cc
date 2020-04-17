#include "contador.h"
#include <iostream>

int main(){
  Contador c;
  std::cout << "valor=" <<c.get()<< '\n';
  c++;
  std::cout << "valor=" <<c.get()<< '\n';
}
