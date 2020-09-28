#ifndef AJUSTE_HPP
#define AJUSTE_HPP
#include <vector>
void ajuste(const std::vector<int> &n, const std::vector<int> &tiemposReales,double &a0,double &a1);
void calcularTiemposEstimados(const std::vector<int> &n, const double &a0, const double &a1,std::vector<int> &tiemposEstimados);
double calcularCoeficienteDeterminacion(const std::vector<int> &tiemposReales, const std::vector <int> &tiemposEstimados);
double calcularTiempoEstimado(const double &n,const double &a0,const double &a1);
#endif
