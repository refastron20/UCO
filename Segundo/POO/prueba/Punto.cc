#include "Punto.h"

punto punto::operator++(void){//prefijo
  x_++;
  y_++;
  return *this;
}
punto punto::operator++(int){//sufijo
  punto p=*this;
  x_++;
  y_++;
  return p;
}
punto punto::operator+(int n){//punto+n
  x_=x_+n;
  return *this;
}
punto operator+(int n, const punto &p){//n+punto
  punto aux=p;
  aux.x_=p.x_+n;
  return aux;
}

punto punto::operator=(const punto &p){
  x_=p.x_;
  y_=p.y_;
  return *this;
}

punto punto::operator=(int &n){
  x_=n;
  return *this;
}
