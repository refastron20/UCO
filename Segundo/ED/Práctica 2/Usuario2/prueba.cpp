#include "Polinomio.hpp"
#include "Monomio.hpp"
#include "operadoresExternosPolinomios.hpp"
#include <iostream>

using namespace ed;
int main(){
  Polinomio p1;

  std::cout << "Escriba p1" << '\n';
  cin>>p1;
  std::cout << "p1=" <<p1<< '\n';

  Monomio m;

  std::cout << "Escriba m" << '\n';
  cin>>m;
  std::cout << "m=" <<m<< '\n';

  std::cout << "p1+m=" <<p1+m<< '\n';
  std::cout << "p1-m" <<p1-m<< '\n';
  std::cout << "p1*m=" <<p1*m<< '\n';





  /*Monomio m;

  std::cout << "Escriba m" << '\n';
  std::cin >> m;
  std::cout << "m=" <<m<< '\n';

  if (p1==m) {
    std::cout << "son iguales" << '\n';
  }else{
    std::cout << "no son iguales" << '\n';
  }*/

  return 0;
}
