#include "jugador.h"
#include <fstream>
#include <string>
#include <iostream>
void Jugador::setApuestas(){
  l_.clear();
  string filename=getDNI()+".txt";
  string aux;
  Apuesta a;
  ifstream file(filename.c_str());
  if(!file.is_open()){
    std::cout<<"No se pudo abrir el archivo\n";
    exit(1);
  }
  do{
    getline(file,aux,',');
    a.tipo=atoi(aux.c_str());
    getline(file,aux,',');
    a.valor=aux;
    getline(file,aux);
    a.cantidad=atoi(aux.c_str());
    l_.push_back(a);
  }while(!(file.eof()));
  l_.pop_back();
  file.close();

}
