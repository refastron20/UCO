#include "Registro.h"
#include <iostream>

using namespace std;

bool Registro::MostrarInfoCiudad(string ciudad){
  list <Ciudad> :: iterator i=c_.begin();
  while(i!=c_.end()){
    if(ciudad==(*i).getNombre()){
      cout<<"Nombre de la ciudad: "<<(*i).getNombre()<<endl;
      cout<<"Kilómetros cuadrados: "<<(*i).getKm2()<<endl;
      return true;
    }
    i++;
  }
  cout<<"No existe la ciudad"<<endl;
  return false;
}

void Registro::MostrarInfoCiudades(){
  list <Ciudad> :: iterator i=c_.begin();
  while(i!=c_.end()){
    MostrarInfoCiudad((*i).getNombre());
    i++;
  }
}

bool Registro::MostrarPorCiudad(string ciudad){
  list <Ciudad> :: iterator i=c_.begin();
  while(i!=c_.end()){
    if(ciudad==(*i).getNombre()){
      cout<<"Listado de las personas de la ciudad "<<ciudad<<endl;
      list <Persona> :: iterator j=p_.begin();
      int n=1;
      while(j!=p_.end()){
        cout<<"Persona número "<<n<<endl;
        cout<<"Nombre: "<<(*j).getNombre()<<" Apellido: "<<(*j).getAPellido()<<" DNI: "<<(*j).getDNI()<<" Peso: "<<(*j).getPeso()<<" Altura: "<<(*j).getAltura()<<endl;
        j++;
        n++;
      }
      return true;
    }
    i++;
  }
  cout<<"No existe la ciudad"<<endl;
  return false;
}

void Registro::MostrarPersonas(){
  list <Ciudad> :: iterator i=c_.begin();
  while(i!=c_.end()){
     MostrarPorCiudad((*i).getNombre());
     i++;
  }
}

void Registro::InsertarPersona(Persona &p){
  p_.push_back(p);
}

bool Registro::BorrarPersona(string DNI){
  list <Persona> :: iterator i=p_.begin();
  while(i!=p_.end()){
     if((*i).getDNI()==DNI){
       p_.erase(i);
       return true;
     }
  }
  cout<<"No se encontró la persona"<<endl;
  return false;
}

void Registro::InsertarCiudad(Ciudad &c){
  c_.push_back(c);
}

bool Registro::BorrarCiudad(string nombre){
  list <Ciudad> :: iterator i=c_.begin();
  while(i!=c_.end()){
     if((*i).getNombre()==nombre){
       c_.erase(i);
       return true;
     }
  }
  cout<<"No se encontró la Ciudad"<<endl;
  return false;
}
