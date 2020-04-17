#ifndef __FUNCIONES_HPP
#define __FUNCIONES_HPP

#include <iostream>
#include <cstring>
#include <cstdlib> //Para usar system
#include <fstream> //Para trabajar con ficheros

#include "grafo.hpp"
#include "algoritmosgrafos.hpp"

using namespace std;
using namespace ed;

int menu()
{
  int opcion;

  system("clear");
  cout << "  0. Salir................................\n";
  cout << "  1. Cargar grafo desde fichero...........\n";
  cout << "  2. Algoritmo de Floyd (GD y GND)......\n";

  cout << "Introduzca opcion...:";
  cin >> opcion;

  return opcion;
}

template <class G_Nodo, class G_Lado>
bool cargarGrafo(Grafo<G_Nodo, G_Lado> * &g)
{
  string ficheroMatriz, ficheroEtiquetas;


  cout << "Fichero de la matriz de conexion: ";
  cin >> ficheroMatriz;

  cout << "Fichero de las etiquetas: ";
  cin >> ficheroEtiquetas;

  ifstream f1(ficheroMatriz.c_str());
  ifstream f2(ficheroEtiquetas.c_str());
  char aux[100];
  int n=0, i=0;

  if(f1.is_open()){
    if(f2.is_open()){

    while(f2.getline(aux,100,'\n')){n++;}


    g = new Grafo < G_Nodo, G_Lado>(n);

    G_Lado **matriz;
    G_Nodo *vector;
    matriz=new G_Lado *[n];
    for (int x = 0; x < n; x++) {
      matriz[x]=new G_Lado [n];
    }
    vector=new G_Nodo [n];

    //Relleno la matriz y vector
    i=0;
    int j;
    while(i<n){
      j=0;
      while(j<(n-1)){
        f1.getline(aux,100,' ');
        matriz[i][j]=atoi(aux);
        j++;
      }
      f1.getline(aux,100);
      matriz[i][n-1]=atoi(aux);
      i++;
    }

    i=0;
    f2.clear();
    f2.seekg(0, f2.beg);
    while (!f2.eof()) {
      f2>>vector[i];
      i++;
    }

    g->setNodos(vector);
    g->setLados(matriz);

    f1.close();
    f2.close();

    return true;

  }else{printf("No se puede abrir el archivo\n");}
    }else{printf("No se puede abrir el archivo\n");}

  return false;

}

template <class G_Nodo, class G_Lado>
void algoritmoFloyd(const Grafo<G_Nodo, G_Lado> &g)
{
  AlgoritmosGrafos <G_Nodo, G_Lado> x;
  G_Lado **m1=g.getLados(), **m2, **m3;

  int n=sizeof(m1[0]);


  m2=new G_Lado *[n];
  for (int i = 0; i < n; i++) {
    m2[i]=new G_Lado [n];
  }

  m3=new G_Lado *[n];
  for (int i = 0; i < n; i++) {
    m3[i]=new G_Lado [n];
  }

  x.Floyd(m1,m2,m3,n);

  int org, dest;
  G_Nodo *v=g.getNodos();

  std::cout << "Ciudades: " << '\n'<<"0:Almeria"<< '\n'<<"1:Cádiz"<< '\n'<<"2:Córdoba"<< '\n'<<"3:Granada"<< '\n'<<"4:Huelva"<< '\n'<<"5:Jaen"<< '\n'<<"6:Málaga"<< '\n'<<"7:Sevilla"<<"\n";
  std::cout << "Ciudad Origen" << '\n';
  std::cin >> org;
  std::cout << "Ciudad destino" << '\n';
  std::cin >> dest;

  std::cout << "Distancia entre " <<v[org]<<" y "<<v[dest]<<":"<<m2[org][dest]<< '\n';

  std::cout << "Camino: "<<v[org]<<" -> ";
  while (m3[org][dest]!=-1) {
    std::cout << v[m3[org][dest]]<<" -> ";
    org=m3[org][dest];
  }
  std::cout << v[dest] << '\n';
}

#endif
