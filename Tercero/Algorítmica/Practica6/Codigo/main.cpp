#include "funcionesMedioNivel.hpp"

int main(int argc, char const *argv[]) {
  int opcion=0;

  do{
    opcion=menu();
    if (opcion==1) {
      nReinasBacktracking();
    }else if (opcion==2) {
      nReinasLasVegas();
    }else if (opcion==3) {
      ajusteCurva();
    }
  }while (opcion!=0);
  return 0;
}
