
#ifndef CIUDAD_H
#define CIUDAD_H
#include <string>
using namespace std;

class Ciudad{

private:

  string nombre_;
  int km2_;

public:
  inline Ciudad(string nombre, int km2){nombre_=nombre;km2_=km2;}
  inline void setNombre(string nombre){nombre_=nombre;};
  inline string getNombre() const {return nombre_;};
  inline void setKm2(int km2){km2_=km2;};
  inline int getKm2() const {return km2_;};

};

#endif
