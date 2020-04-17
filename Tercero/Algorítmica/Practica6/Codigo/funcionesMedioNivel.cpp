#include "funcionesMedioNivel.hpp"
#include "reinasBacktracking.hpp"
#include "reinasLasVegas.hpp"
#include "ClaseTiempo.cpp"
#include "ajusteCurva.hpp"

#include <iostream>
#include <vector>
#include <fstream>

int menu(){
  int opcion, reinas;
  std::cout << "1.- Mostrar las soluciones del Problema de las n Reinas por backtracking" << '\n';
  std::cout << "2.- Mostrar una solución del Problema de las n Reinas por el algoritmo de Las Vegas" << '\n';
  std::cout << "3.- Ajustar la curva de tiempos" << '\n';
  std::cout << "0.- Salir" << '\n';
  do{
    std::cin>>opcion;
    if (opcion!=1 and opcion!=2 and opcion!=3 and opcion!=0) {
      std::cout << "Opción no válida" << '\n';
      opcion=-1;
    }
    if (opcion==0) {
      std::cout << "Saliendo..." << '\n';
    }
  }while (opcion==-1);
  return opcion;
}

void nReinasBacktracking() {
  int n;
  std::cout << "Introduzca el número de reinas" << '\n';
  std::cin >> n;
  std::vector<std::vector<int>> v;
  BacktrackingQueens(n,v);
  std::cout  << '\n';
  std::cout  << '\n';
  std::cout << "Hay " <<v.size()<<" soluciones"<< '\n';
  for (unsigned int i = 0; i < v.size(); i++) {
    std::cout << "Solucion "<<i+1<<": ";
    for (int j = 1; j < v[i].size(); j++) {
      std::cout << v[i][j]<<" ";
    }
    std::cout  << '\n';
  }
  std::cout  << '\n';
  std::cout  << '\n';
  std::cout  << '\n';
}

void nReinasLasVegas() {
  int n;
  std::cout << "Introduzca el número de reinas" << '\n';
  std::cin >> n;
  std::vector<int> v;
  int intentos=1;
  while (!LasVegasQueens(n,v)) {
    intentos++;
  }
  std::cout << "Se han necesitado un total de "<<intentos<<" intentos" << '\n';
  std::cout << "La solución es: ";
  for (unsigned int i = 1; i < v.size(); i++) {
    std::cout << v[i] <<" ";
  }
  std::cout  << '\n';
}

void ajusteCurva() {
  int minimo,maximo;

  Clock time;

  std::vector<std::vector<int> > v;
  std::vector<int> tiemposReales;
  std::vector<int> n;
  std::vector<int> tiemposEstimados;

  double a0,a1;

  std::cout << "Introduzca el rango de n: " << '\n';
  std::cout << "Mínimo:" << '\n';
  std::cin >> minimo;
  std::cout << "Máximo: " << '\n';
  std::cin >> maximo;
  for (int i = minimo; i <=maximo; i++) {
    time.start();
    BacktrackingQueens(i,v);
    time.stop();
    tiemposReales.push_back(time.elapsed());
    n.push_back(i);
    v.clear();
  }

  ajuste(n,tiemposReales,a0,a1);
  calcularTiemposEstimados(n,a0,a1,tiemposEstimados);

  std::ofstream fich("../tiempos.txt");
  if (!fich.is_open()) {
    std::cerr << "No se pudo abrir el fichero, saliendo..." << '\n';
  }
  for (unsigned int i = 0; i < n.size(); i++) {
    fich<<n[i]<<" "<<tiemposReales[i]<<" "<<tiemposEstimados[i]<<std::endl;
  }
  fich.close();

  std::cout << "Ecuación de la curva ajustada= " <<a0<<"+"<<a1<<"!"<< '\n';
  double coef;
  coef=calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);
  std::cout << "coeficiente de determinación= " <<coef<< '\n';

  double NumeroN=1;
  coef=0;
  //calculamos el tiempo para ordenar un vector de N elementos que introduce el usuario por teclado
  //Si introduce 0 salimos
  do{
    std::cout << "Para que N quiere calcular el tiempo?" << '\n';
    std::cin >> NumeroN;
    if (NumeroN!=0) {
      coef=calcularTiempoEstimado(NumeroN,a0,a1);
      std::cout << "Tardaría " <<coef<<" días para ordenar un vector de "<<NumeroN<<" elementos"<< '\n';
    }
  }while(NumeroN!=0);
}
