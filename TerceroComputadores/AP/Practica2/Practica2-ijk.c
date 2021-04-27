#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define TAMMAT 6000
#define TAMBUCLE 6000


struct params{
  int inicio_i;
  int final_i;
  int inicio_j;
  int final_j;
};

float A[TAMMAT][TAMMAT], B[TAMMAT][TAMMAT], Cparalelo[TAMMAT][TAMMAT], Cserie[TAMMAT][TAMMAT];

void *multi(void *ini){

  struct params *p = (struct params *) ini;
  for (unsigned i = p->inicio_i; i < p->final_i; i++) {
    for (unsigned j = p->inicio_j; j < p->final_j; j++) {
      for (unsigned k = 0; k < TAMBUCLE; k++) {
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
  int SALTO = TAMMAT/(NHILOS/2);

  pthread_t hilos[NHILOS];
  int status;

  struct params p[NHILOS];

  if (NHILOS== 8) {
    int cont = 0;
    for (unsigned i = 0; i < 2; i++) {
      for (unsigned j = 0; j < 4; j++) {
        p[cont].inicio_i = i*SALTO*2;
        p[cont].final_i = p[cont].inicio_i + SALTO*2;
        p[cont].inicio_j = j*SALTO;
        p[cont].final_j = p[cont].inicio_j + SALTO;
        cont++;
      }
    }
  }else{
    int cont = 0;
    for (unsigned i = 0; i < sqrt(NHILOS); i++) {
      for (unsigned j = 0; j < sqrt(NHILOS); j++) {
        p[cont].inicio_i = i*SALTO;
        p[cont].final_i = p[cont].inicio_i + SALTO;
        p[cont].inicio_j = j*SALTO;
        p[cont].final_j = p[cont].inicio_j + SALTO;
        cont++;
      }
    }
  }


  for (unsigned i = 0; i < NHILOS; i++) {
    fprintf(stderr, "p[%d].inicio_i = %d\n",i, p[i].inicio_i );
    fprintf(stderr, "p[%d].final_i = %d \n",i, p[i].final_i );
    fprintf(stderr, "p[%d].inicio_j = %d\n",i, p[i].inicio_j );
    fprintf(stderr, "p[%d].final_j = %d\n",i, p[i].final_j );
  }

  for (unsigned i = 0; i < TAMBUCLE; i++) {
    for (unsigned j = 0; j < TAMBUCLE; j++) {
      A[i][j] = rand()%10;
      B[i][j] = rand()%10;
      Cserie[i][j] = 0;
      Cparalelo[i][j] = 0;
    }
  }

  for (int i = 0; i < NHILOS; i++) {
      if ((status = pthread_create(&hilos[i], NULL, multi, (void *) &(p[i]))))
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


  /*fprintf(stderr, "Iniciando multiplicación en serie...\n" );
  double t_ini_serie = clock();
  for (unsigned i = 0; i < TAMBUCLE; i++) {
    for (unsigned j = 0; j < TAMBUCLE; j++) {
      for (unsigned k = 0; k < TAMBUCLE; k++) {
        Cserie[i][j] += A[i][k]*B[k][j];
      }
    }
  }
  double t_final_serie = clock();
  fprintf(stderr, "Multiplicación en serie terminada\n" );
  double t_total_serie = (t_final_serie - t_ini_serie)/CLOCKS_PER_SEC;
  printf("El tiempo total en serie es %f\n", t_total_serie);


  for (unsigned i = 0; i < TAMBUCLE; i++) {
    for (unsigned j = 0; j < TAMBUCLE; j++) {
      if (Cparalelo[i][j] != Cserie[i][j]) {
        fprintf(stderr, "Cparalelo[%d][%d]=%f, Cserie[%d][%d]=%f\n",i,j,Cparalelo[i][j],i,j,Cserie[i][j] );
        fprintf(stderr, "error al multiplicar\n" );
        exit(-1);
      }
    }
  }*/
}
