#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAMMAT 4000
#define TAMBUCLE 4000
float A[TAMMAT][TAMMAT], B[TAMMAT][TAMMAT], C[TAMMAT][TAMMAT];

int main(){
  srand(time(0));


  for (unsigned i = 0; i < TAMBUCLE; i++) {
    for (unsigned j = 0; j < TAMBUCLE; j++) {
      A[i][j] = rand()%10;
      B[i][j] = rand()%10;
      C[i][j] = 0;
    }
  }


  //omp_set_numthreads(8);
  double t_ini = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for nowait
      for (unsigned i = 0; i < TAMBUCLE; i++) {
        for (unsigned k = 0; k < TAMBUCLE; k++) {
          for (unsigned j = 0; j < TAMBUCLE; j++) {
            C[i][j] += A[i][k]*B[k][j];
          }
        }
      }
  }
  double t_final = omp_get_wtime();

  double t_total = (t_final - t_ini);

  printf("C[5][5]= %f\n",C[5][5] );
  printf("El tiempo total es %f\n", t_total);
}
