#include "Monomio.hpp"
#include "funcionesExtra.hpp"
#include <iostream>
#include <cmath>

void ed::concatenar(ed::Monomio &m1,ed::Monomio &m2,ed::Monomio &m3){
  ed::Monomio v[3]={ m1, m2, m3};
  ed::Monomio aux;
  for (int j = 1; j < 3; j++) {
    for (int i = 0; i < 3-i; i++) {
      if (v[i].getGrado()<v[i+1].getGrado()) {
        aux=v[i];
        v[i]=v[i+1];
        v[i+1]=aux;
      }
    }
  }
  v[0].escribirMonomio();
  std::cout<<"+";
  v[1].escribirMonomio();
  std::cout << "+";
  v[2].escribirMonomio();
}

void ed::calcularPolinomio2(ed::Monomio const &m1, double const &x){
  double p;
  if ((m1.getGrado()>2)) {
    std::cout << "El polinomio tiene grado mayor a dos" << '\n';
  }else{
    #ifndef NDEBUG
      assert((m1.getGrado()<=2));
    #endif
    if (m1.getGrado()==0) {
      std::cout << "Al ser el polinomio de grado 0 se sumarán los dos números" << '\n';
      std::cout << "El resultado es " <<m1.getCoeficiente()+x<< '\n';    }
    if (m1.getGrado()==1) {
        p=(-x)/m1.getCoeficiente();
        std::cout << " Polinomio de grado 1 "<<"\n"<<"X=" <<p<< '\n';
      }
    if (m1.getGrado()==2) {
      if((-x)>0){
        p=sqrt((-x)/m1.getCoeficiente());
        std::cout << " Polinomio de grado 2"<<"\n"<<"X=+/-" <<p<< '\n';
      }else
        std::cout << "No tiene solución real" << '\n';
    }
  }
}

void ed::calcularPolinomio2(double const &m1, double const &m2, double const &x){
  double p[2];
  if ((4*m1*x)>(m2*m2))
    std::cout << "No tiene solución real" << '\n';
  else{
    p[0]=-((m2)+sqrt((m2*m2)-4*m1*x))/(2*m1);
    p[1]=-((m2)-sqrt((m2*m2)-4*m1*x))/(2*m1);
    std::cout << "x1=" <<p[0]<<'\n'<<"x2="<<p[1]<<"\n";
  }
}
