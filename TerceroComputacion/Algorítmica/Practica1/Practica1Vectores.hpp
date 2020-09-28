#ifndef PRACTICA1_H
#define  PRACTICA1_H

#include <vector>

void funcionVector();
//Función que se encargará de hacer las llamadas a las demás funciones así como las operaciones intermedias

void quicksort(int izq, int der, std::vector <int> &v);
//Función que realiza la ordeanación por medio del algortimo Quicksort
//Le pasamos el inicio(izq),el final(der) y el vector al ordenar(v)

void rellenaVector(std::vector <int> &v);
//Función que rellena un vector
//Su único parametro es el vector a rellenar

bool estaOrdenado(const std::vector <int> &v);
//Función que comprueba si un vector está ordenado
//Se le pasa el vector a comprobar
//Devuelve true si está ordenado o false si no lo está

void ajusteNlogN(std::vector <double> &n, std::vector <double> &tiemposReales, double &a0, double &a1);
//Función que realiza el ajuste de una curva con el cambio de variable z=nlogn
//Le pasamos el vector de números de elementos(n), el vector de los tiempos reales medidos(tiemposReales)
//y dos variables que serán los términos a calcular(a0 y a1)

void calcularTiemposEstimadosNlogN(const std::vector <double> &n, const double &a0, const double &a1, std::vector <double> &tiemposEstimados);
//Función para calcular los tiempos estimados a partir de los reales y la curva estimada
//Le pasamos el vector de número de elementos(n), el vector de tiempos reales(tiemposReales)
//y las variables de la ecuación de curva(a0 y a1)

double calcularCoeficienteDeterminacion(const std::vector <double> &tiemposReales, const std::vector <double> &tiemposEstimados);
//Función que calcula el coeficiente de determinación entre los tiempos reales y estimados
//Le pasamos los vectores de tiempos reales(tiemposReales) y estimados(tiemposEstimados)

double calcularTiempoEstimadoNlogN(const double &n, const double &a0, const double &a1);
//Función que calcula el tiempo estimado para un número n de elementos
//Le pasamos el número de elementos(n) y los términos de la ecuación de curva(a0 y a1)

#endif
