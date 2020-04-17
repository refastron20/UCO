//Clase Registro que guarda una lista de personas y te permite operar con ellas.
#ifndef REGISTRO_H
#define REGISTRO_H

#include "Persona.h"//archivo de clase Persona
#include "Ciudad.h"
#include <list>

using namespace std;

class Registro{

private:
  list <Ciudad> c_;
  list <Persona> p_;

public:

  void MostrarInfoCiudades();//Muestra la información de las ciudades
  bool MostrarInfoCiudad(string ciudad);//Muestra información de una ciudad;
  void InsertarCiudad(Ciudad &c);//Inserta en la lista según la ciudad
  bool BorrarCiudad(string nombre);//solo se borra por nombre

  void MostrarPersonas();//Muestra la lista por ciudad
  bool MostrarPorCiudad(string ciudad);//Muestra según la ciudad
  void InsertarPersona(Persona &p);//Inserta en la lista según la ciudad
  bool BorrarPersona(string DNI);//solo se borra por DNI
  /*void OrdenarLista(string ciudad);//ordena la lista según la ciudad
  void GuardarInfo();
  bool CargarInfo();*/

};

#endif
