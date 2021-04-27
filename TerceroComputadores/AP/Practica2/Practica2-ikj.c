#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAMMAT 6000

float A[TAMMAT][TAMMAT], B[TAMMAT][TAMMAT], Cparalelo[TAMMAT][TAMMAT], Cserie[TAMMAT][TAMMAT];

void *multi(void *ini){
  //Cparalelo[0][0] = 1;
  int inicio = ((int *)  ini)[0];
  int final = ((int *) ini)[1];
  for (unsigned i = inicio; i < final; i++) {
    for (unsigned k = 0; k < TAMMAT; k++) {
      for (unsigned j = 0; j < TAMMAT; j++) {
        Cparalelo[i][j] += A[i][k]*B[k][j];
      }
    }
  }
}


int main(int argc, char *argv[]){
  srand(time(0));


  if(argc!=2){
		printf("Falta número de hilos\n");
		return -1;
	}
  int NHILOS = atoi(argv[1]);
  int SALTO = TAMMAT/NHILOS;

  pthread_t hilos[NHILOS];
  int v[NHILOS][2];
  int status;

  v[0][0] = 0;
  v[0][1] = SALTO;
  for (unsigned i = 1; i < NHILOS; i++) {
    v[i][0] = v[i-1][0]+SALTO;
    v[i][1] = v[i][0]+SALTO;
  }

  for (unsigned i = 0; i < TAMMAT; i++) {
    for (unsigned j = 0; j < TAMMAT; j++) {
      A[i][j] = rand()%10;
      B[i][j] = rand()%10;
      Cserie[i][j] = 0;
      Cparalelo[i][j] = 0;
    }
  }


  for (int i = 0; i < NHILOS; i++) {
      if ((status = pthread_create(&hilos[i], NULL, multi, (void *) &v[i])))
      exit(status);
  }

  fprintf(stderr, "Iniciando multiplicación en paralelo...\n" );
  double t_ini = clock();
  for (int i = 0; i < NHILOS; i++) {
     pthread_join(hilos[i], NULL);
  }
  double t_final = clock();
  fprintf(stderr, "Multiplicación en paralelo terminada\n" );
  double t_total_paralelo = (t_final - t_ini)/CLOCKS_PER_SEC;
  printf("El tiempo total en paralelo es %f\n", t_total_paralelo);
}
