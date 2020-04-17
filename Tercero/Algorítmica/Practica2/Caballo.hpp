#ifndef CABALLO_HPP
#define CABALLO_HPP

#include <iostream>
#include <vector>

typedef struct punto{
  int a1,a2;
}punto;

int caballo(int f, int c, std::vector <punto> v, std::vector <std::vector <punto> > &vPadre){
  //si llegamos a un camino fuera de los límites del tablero, ese camino no sería válido y devolvemos 0

    if ((c<1 or c>8) or (f<1 or f>8)){
      return 0;
    }

    punto point;
    point.a1=f;point.a2=c;
    v.push_back(point);
    if((f==1)){
      vPadre.push_back(v);
      return 1;
    }

  return (caballo(f-2, c+1, v, vPadre)+caballo(f-2, c-1, v, vPadre)+caballo(f-1, c+2, v, vPadre)+caballo(f-1, c-2, v, vPadre));
}

void caminosGraficos(std::vector <punto> &v){
  for (unsigned int j = 0; j < v.size(); j++) {
    std::cout << "( " << v[j].a1<<" , "<<v[j].a2<<" )";
  }
  std::cout  << '\n';
  int n=0;
  for (int i = 8; i >0; i--) {
    std::cout << "---------------------------------" << '\n';
    std::cout << "|";
    for (int j = 1; j <=8; j++) {
      if (v[n].a1==i and v[n].a2==j) {
        std::cout << " x |";
        n++;
      }else{
        std::cout << "   |";
      }
    }
    std::cout  << '\n';
  }
  std::cout << "---------------------------------" << '\n';
}

#endif
