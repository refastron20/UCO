

#ifndef JUGADOR_H
#define JUGGADOR_H

#include "persona.h"
#include <list>
typedef struct Apuesta{
  int tipo;
  string valor;
  int cantidad;
}Apuesta;

class Jugador : public Persona{
private:
  int dinero_;
  string codigo_;
  list<Apuesta> l_;
public:
  inline Jugador(string DNI,string codigo, string nombre="",string apellidos="",int edad=0,string direccion="",
		           string localidad="",string provincia="",string pais="") : Persona (DNI, nombre, apellidos, edad,
		            direccion, localidad, provincia, pais){
                  codigo_=codigo;dinero_=1000;}
  inline void setCodigo(string codigo){codigo_=codigo;}
  inline string getCodigo() const {return codigo_;}
  inline void setDinero(int dinero){dinero_=dinero;}
  inline int getDinero() const {return dinero_;}
  inline list<Apuesta> getApuestas() const {return l_;}
  void setApuestas();


};


#endif
