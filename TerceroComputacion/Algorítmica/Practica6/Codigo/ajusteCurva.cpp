#include "funcionesMatematicas.hpp"
#include "sistemaEcuaciones.hpp"
#include "ajusteCurva.hpp"
#include <vector>


void ajuste(const std::vector<int> &n, const std::vector<int> &tiemposReales,double &a0,double &a1){
  double x=0, t=0, xt=0, aux=0, x2=0.0;
  for (int i = 0; i < n.size(); i++) {
    aux=n[i]*factorial(n[i]);
    x+=aux;
    x2+=pow(aux,2);
    t+=tiemposReales[i];
    xt+=aux*tiemposReales[i];
  }

  vector < vector < double > > A;
  A = vector< vector< double > >(2, vector< double > (2));

  //rellenamos la matriz A
  A[0][0]=n.size();
  A[0][1]=x;
  A[1][0]=x;
  A[1][1]=x2;

  vector < vector < double > > B;
  B = vector< vector< double > >(2, vector< double > (1));

  //Rellenamos la matriz B
  B[0][0]=t;
  B[1][0]=xt;

  vector < vector < double > > X;
  X = vector< vector< double > >(2, vector< double > (2));

  //Resolvemos el sistema y le asignamos el valor a a0 y a1
  resolverSistemaEcuaciones(A,B,2,X);
  a0=X[0][0];
  a1=X[1][0];
}

void calcularTiemposEstimados(const std::vector<int> &n, const double &a0, const double &a1,std::vector<int> &tiemposEstimados){
  int m=n.size();
  tiemposEstimados.resize(m);
  for (int i = 0; i < m; i++) {
    tiemposEstimados[i]=a0+(a1*n[i]*factorial(n[i]));
  }
}

double calcularCoeficienteDeterminacion(const vector <int> &tiemposReales, const vector <int> &tiemposEstimados){
  double varianzaReales,varianzaEstimados;

  varianzaReales=varianza(tiemposReales);
  varianzaEstimados=varianza(tiemposEstimados);

  return varianzaEstimados/varianzaReales;
}

double calcularTiempoEstimado(const double &n,const double &a0,const double &a1){
  return ((((a0+(a1*n*factorial(n)))/1000000)/60)/60)/24;
}
