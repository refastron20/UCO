#include <iostream>
#include "Caballo.hpp"
#include <vector>
#include <cstdlib>

int main(){
  std::vector <punto> v;
  std::vector <std::vector <punto> > vPadre;
  int c, op;


  do{

    vPadre.clear();

    system("clear");

    std::cout << "1.- Cálculo de los caminos posibles para llegar a una casilla de la fila 8 desde cualquier casilla de la fila 1" << '\n';
    std::cout << "2.- Cálculo de los caminos posibles para llegar a la fila 8 desde la casilla inicial (1,2)" << '\n';
    std::cout << "3.- Cálculo de los caminos posibles para llegar a la fila 8 desde la casilla inicial (1,7)" << '\n';
    std::cout << "0.- Salir" << '\n';
    std::cin>> op;
    std::cin.ignore();
    switch(op){
      case 1:
        do{
          std::cout << "Introduzca la columna(c) a la que quiere llegar (1<c<8)" << "\n";
          std::cin>>c;
          if (c<1 or c>8) {
            std::cout << "c tiene que estar compredido entre 1 y 8" << "\n";
          }
        }while(c<1 and c>8);
        std::cout << "Caminos posibles: " << caballo(8,c,v,vPadre)<<"\n";
        for (unsigned int i = 0; i < vPadre.size(); i++) {
          std::cout << "Camino: " <<i+1<<" ";
          for (unsigned int j = 0; j < vPadre[i].size(); j++) {
            std::cout << "( " << vPadre[i][j].a1<<" , "<<vPadre[i][j].a2<<" )";
          }
          std::cout << '\n';
        }
        std::cout << "¿Quiere mostrar los caminos graficamente?" << '\n';
        std::cin.ignore();
        for (unsigned int i = 0; i < vPadre.size(); i++) {
          std::cout << "Camino " <<i+1<< '\n';
          caminosGraficos(vPadre[i]);
          std::cin.ignore();
        }
        std::cin.ignore();
      break;
      case 2:
        std::cout << "Caminos posibles: " << caballo(8,2,v,vPadre)<<"\n";
        for (unsigned int i = 0; i < vPadre.size(); i++) {
          std::cout << "Camino: " <<i+1<<" ";
          for (unsigned int j = 0; j <  vPadre[i].size(); j++) {
            std::cout << "( " << abs(vPadre[i][j].a1-9)<<" , "<<vPadre[i][j].a2<<" )";
          }
          std::cout << '\n';
        }
        std::cin.ignore();
      break;
      case 3:
      std::cout << "Caminos posibles: " << caballo(8,7,v,vPadre)<<"\n";
      for (unsigned int i = 0; i < vPadre.size(); i++) {
        std::cout << "Camino: " <<i+1<<" ";
        for (unsigned int j = 0; j <  vPadre[i].size(); j++) {
          std::cout << "( " << abs(vPadre[i][j].a1-9)<<" , "<<vPadre[i][j].a2<<" )";
        }
        std::cout << '\n';
      }
      std::cin.ignore();
      break;
      case 0:
        std::cout << "Saliendo..." << '\n';
      break;
      default:
      std::cout << "opción incorrecta" << '\n';
    }
  }while(op!=0);
}
