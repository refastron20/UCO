#include "dynamicprogrammingmethod.hpp"
#include <limits>
#include "algorithm.hpp"
#include "digitalcurve.hpp"

DynamicProgrammingMethod::DynamicProgrammingMethod(char *fileName,int &points){
 //A digital curve is created to load the digital curve in file
 DigitalCurve dc(fileName);

 //Digital curve as saved as original curve
 this->setOriginalCurve(dc);

 this->setNumberPointsPolygonalApproximation(points);
}

DynamicProgrammingMethod::~DynamicProgrammingMethod(){
}

void DynamicProgrammingMethod::apply(){
  //n=puntos curva
  //m=puntos aproximacion
  //E(n,m)=min{E(j,m-1),e(Pj-1,Pn-1)}
  //tamFather{n+1,m+1}
  //father[i,j]=i y al final father-1
  this->calculateSummations();

  int N=this->getOriginalCurve().getNumberPointsDigitalCurve();
  int M=this->getNumberPointsPolygonalApproximation();

  std::vector< std::vector< long double > > E;
  E = std::vector< std::vector< long double > >(N, vector< long double >(M));
  for (int i = 0; i < N; i++) {
    E[i][0]=numeric_limits<long double>::max();
  }
  for (int m = 2; m < M; m++) {
    for (int n = m; n < N; n++) {
      for (int j = m-1; j < n-1; j++) {
        E[n][m]=std::min(E[j][m-1],this->calculateISEValue(j-1,n-1));
      }
    }
  }
}
