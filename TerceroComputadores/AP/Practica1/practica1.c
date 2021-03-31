#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  srand(time(0));
  float A[512][512], B[512][512], C[512][512];


  for (unsigned i = 0; i < 512; i++) {
    for (unsigned j = 0; j < 512; j++) {
      A[i][j] = rand()%10;
      B[i][j] = rand()%10;
      C[i][j] = 0;
    }
  }



  double t_ini = clock();
  for (unsigned i = 0; i < 512; i++) {
    for (unsigned j = 0; j < 512; j++) {
      for (unsigned k = 0; k < 512; k++) {
        C[i][j] += A[i][k]*B[k][j];
      }
    }
  }
  double t_final = clock();

  double t_total = (t_final - t_ini)/CLOCKS_PER_SEC;

  printf("C[5][5]= %f\n",C[5][5] );
  printf("El tiempo total es %f\n", t_total);
}
