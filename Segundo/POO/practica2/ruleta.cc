#include "ruleta.h"
#include <list>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

bool Ruleta::addJugador(Jugador jugador){
  list<Jugador>::iterator i;
  i=jugadores_.begin();
  while(i!=jugadores_.end()){
    if((*i).getDNI()==jugador.getDNI())
      return false;
    i++;
  }
  jugadores_.push_back(jugador);
  string filename=jugador.getDNI()+".txt";
  ifstream file(filename.c_str());
  if(file.is_open()){
    file.close();
    return true;
  }else{
    ofstream file2(filename.c_str());
    file.close();
    return true;
  }
}

int Ruleta::deleteJugador(Jugador jugador){
  return deleteJugador(jugador.getDNI());
}
int Ruleta::deleteJugador(string cad){
  if(jugadores_.empty())
    return -1;
  list<Jugador>::iterator i;
  i=jugadores_.begin();
  while(i!=jugadores_.end()){
    if((*i).getDNI()==cad){
      jugadores_.erase(i);
      return 1;
    }
    i++;
  }
  return -2;
}

void Ruleta::escribeJugadores(){
    list<Jugador>::iterator i=jugadores_.begin();
    ofstream file("Jugadores.txt");
    while(i!=jugadores_.end()){
      file<<(*i).getDNI()<<","<<(*i).getCodigo()<<","<<(*i).getNombre()<<","<<(*i).getApellidos()
      <<","<<(*i).getDireccion()<<","<<(*i).getLocalidad()<<","<<(*i).getProvincia()
      <<","<<(*i).getPais()<<","<<(*i).getDinero()<<"\n";
      i++;
    }
    file.close();
}

void Ruleta::leeJugadores(){
  string aux;
  Jugador j("dni","cod");
  int dinero;
  jugadores_.clear();
  ifstream file("Jugadores.txt");
  while(!file.eof()){
    getline(file,aux,',');
    j.setDNI(aux);
    getline(file,aux,',');
    j.setCodigo(aux);
    getline(file,aux,',');
    j.setNombre(aux);
    getline(file,aux,',');
    j.setApellidos(aux);
    getline(file,aux,',');
    j.setDireccion(aux);
    getline(file,aux,',');
    j.setLocalidad(aux);
    getline(file,aux,',');
    j.setProvincia(aux);
    getline(file,aux,',');
    j.setPais(aux);
    getline(file,aux);
    dinero=atoi(aux.c_str());
    j.setDinero(dinero);
    jugadores_.push_back(j);
  }
  jugadores_.pop_back();
  file.close();
}

void Ruleta::getPremios(){
  int encontrado=0;
  string aux;
  Apuesta a;
  int rojos[]={1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
  int negros[]={2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
  list<Jugador>::iterator i=jugadores_.begin();
  while(i!=jugadores_.end()){
    string filename=(*i).getDNI()+".txt";
    ifstream file(filename.c_str());
    while(!file.eof()){
      getline(file,aux,',');
      a.tipo=atoi(aux.c_str());
      getline(file,aux,',');
      a.valor=aux;
      getline(file,aux);
      a.cantidad=atoi(aux.c_str());
      switch(a.tipo){
        case 1:
          if (bola_==atoi(a.valor.c_str())) {
            (*i).setDinero((*i).getDinero()+(a.cantidad*35));
            setBanca(getBanca()-(a.cantidad*35));
          }else{
            (*i).setDinero((*i).getDinero()-a.cantidad);
            setBanca(getBanca()+a.cantidad);
          }
          break;
        case 2:
          if(a.valor=="rojo"){
            for (int j = 0; j < 18; j++){
              if(bola_==rojos[j]){
                (*i).setDinero((*i).getDinero()+a.cantidad);
                setBanca(getBanca()-a.cantidad);
                encontrado++;
              }
            }
            if(encontrado==0){
              (*i).setDinero((*i).getDinero()-a.cantidad);
              setBanca(getBanca()+a.cantidad);
            }
          }else{
              encontrado=0;
              for (int j = 0; j < 18; j++){
                if(bola_==negros[j]){
                  (*i).setDinero((*i).getDinero()+a.cantidad);
                  setBanca(getBanca()-a.cantidad);
                  encontrado++;
                }
              }
              if (encontrado==0){
                (*i).setDinero((*i).getDinero()-a.cantidad);
                setBanca(getBanca()+a.cantidad);
              }
            }
          break;
        case 3:
            if((((a.valor=="par")&&(bola_%2==0))||((a.valor=="impar")&&((bola_%2)!=0)))&&(bola_!=0)){
              (*i).setDinero((*i).getDinero()+a.cantidad);
              setBanca(getBanca()-a.cantidad);
          }else{
            (*i).setDinero((*i).getDinero()-a.cantidad);
            setBanca(getBanca()+a.cantidad);
          }
          break;
        case 4:
          if(((a.valor=="bajo")&&((bola_<=18)&&(bola_>0)))||((a.valor=="alto")&&(bola_>18))){
            (*i).setDinero((*i).getDinero()+a.cantidad);
            setBanca(getBanca()-a.cantidad);
          }else{
            (*i).setDinero((*i).getDinero()-a.cantidad);
            setBanca(getBanca()+a.cantidad);
          }
      }
    }
    i++;
    file.close();
  }
}
