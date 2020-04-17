#include "Entero.hpp"
#include <iostream>
#include <string>

int main(){
  int salir=0,opcion;
  Entero n1,n2;
  while (salir!=1) {
    std::cout << "1.Suma de dos enteros" << '\n';
    std::cout << "2.Multiplicacion de dos enteros" << '\n';
    std::cout << "3.Factorial de un entero" << '\n';
    std::cout << "0.Salir" << '\n';
    std::cin >> opcion;

    switch (opcion) {
      case 1:
        std::cout << "Entero 1:" << '\n';
        std::cin >> n1;
        std::cout << "Entero 2:" << '\n';
        std::cin >> n2;
        std::cout << "n1+n2=" <<n1+n2<< '\n';
        break;
        case 2:
          std::cout << "Entero 1:" << '\n';
          std::cin >> n1;
          std::cout << "Entero 2:" << '\n';
          std::cin >> n2;
          std::cout << "n1*n2=" <<n1*n2<< '\n';
          std::cout << "Resultado 2= " <<n1.multiplicar(n2)<< '\n';
          break;
        case 3:
          std::cout << "Entero:" << '\n';
          std::cin >> n1;
          std::cout << "n1!=" <<n1.factorial()<< '\n';
          break;
        case 0:
          std::cout << "Saliendo..." << '\n';
          salir=1;
          break;
        default:
          std::cout << "Opción invalida" << '\n';
    }
    if (salir!=1) {
      std::cout << "Pulse enter para continuar" << '\n';
      cin.ignore();
      cin.ignore();
    }
  }
}
