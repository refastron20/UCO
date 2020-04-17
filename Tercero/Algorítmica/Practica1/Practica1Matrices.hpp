#ifndef PRACTICA1MATRICES_HPP
#define PRACTICA1MATRICES_HPP

#include <vector>

using namespace std;

void funcionMatrices();
//Función qu ellamará a las demás

void rellenarMatriz(vector<vector <double> > &v);
//Función para rellenar una matriz
//Le pasamos v que será la matriz a rellenar

void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);
//Función que realiza el ajuste polinómico a un polinomio de grado 3 y guarda los coeficientes en a
//Le pasamos n que es el vector de número de elementos,
//tiemposReales que es el vector de tiempos reales y
//a que es el vector de coeficientes

void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &a, vector <double> &tiemposEstimados);
//Función que calcula los tiempos estimados para un polinomio de grado 3 y los guarda en tiemposEstimados
//Le pasamos n que es el vector de número de elementos,
//a que es el vector de coeficientes y
//tiemposEstimados que es el vector de tiempos estimados


double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a);
//Función que calcula el tiempo estimado para un valor n concreto
//Le pasamos n que es el numero de elementos y
//a que es el vector de coeficientes
//Nos devuelve el tiempo estimado en días para el n que le especificamos

#endif
