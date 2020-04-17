
#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

class Persona{

private:

  string nombre_;
  string apellido_;
  string DNI_;
  int peso_;
  int altura_;
  string ciudad_;//FK de clase ciudad

public:
  inline Persona(string nombre, string apellido, string DNI, string ciudad, int peso=0, int altura=0){ciudad_=ciudad;nombre_=nombre;apellido_=apellido;DNI_=DNI;peso_=peso;altura_=altura;}
  inline void setNombre(string nombre){nombre_=nombre;};
  inline string getNombre() const {return nombre_;};
  inline void setApellido(string apellido){apellido_=apellido;};
  inline string getAPellido() const {return apellido_;};
  inline void setDNI(string DNI){DNI_=DNI;};
  inline string getDNI() const {return DNI_;};
  inline void setPeso(int peso){peso_=peso;};
  inline int getPeso() const {return peso_;};
  inline void setAltura(int altura){altura_=altura;};
  inline int getAltura() const {return altura_;};
  inline void setCiudad(string ciudad){ciudad_=ciudad;};
  inline string getCiudad() const {return ciudad_;};

};

#endif
