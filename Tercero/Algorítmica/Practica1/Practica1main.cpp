#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Practica1Vectores.hpp"
#include "Practica1Matrices.hpp"

using namespace std;

int main(){
  //iniciamos la semilla para los numeros aleatorios
  srand(time(NULL));
  int op=0;

  do{
    cout << "Elija opción:" << '\n';
    cout << "1. Quicksort" << '\n';
    cout << "2. Multiplicacion de Matrices" << '\n';
    cout << "0. Salir" << '\n';
    cin >> op;

    switch(op){
      case 1:
        funcionVector();
      break;
      case 2:
        funcionMatrices();
      break;
      case 0:
        cout << "Saliendo.." << '\n';
      break;
      default:
        cout << "Opción incorrecta" << '\n';
    }
  }while(op!=0);
}
