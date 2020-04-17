#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

#define NITER 99
#define N 5

int buffer[N];
int n;
int indp=0;
int indc=0;
int sump=0, sumc=0;
sem_t sc, s, sp;

void *Productor();
void *Consumidor();

int main(){
  pthread_t P, C;
  srand(time(NULL));
  sem_init(&s, 0, 1);
  sem_init(&sc, 0, 0);
  sem_init(&sp, 0, N);

  if(pthread_create(&P, NULL, &Productor, NULL)!=0){
    printf("No se pudo crear el hilo\n");
    exit(1);
  }

  if(pthread_create(&C, NULL, &Consumidor, NULL)!=0){
    printf("No se pudo crear el hilo\n");
    exit(1);
  }


  pthread_join(P, NULL);
  pthread_join(C, NULL);

  printf("La suma del productor es %d\n",sump );
  printf("La suma del consumidor es %d\n",sumc );

}

void *Productor(){
  for (size_t i = 0; i < NITER; i++) {
    n=rand()%1001;
    printf("El productor produce %d\n",n );
    sem_wait(&sp);
    sem_wait(&s);
    buffer[indp]=n;
    sump+=n;
    indp=(indp+1)%N;
    sem_post(&s);
    sem_post(&sc);
  }
  pthread_exit(NULL);
}


void *Consumidor(){
  for (size_t i = 0; i < NITER; i++) {
    sem_wait(&sc);
    sem_wait(&s);
    sumc+=buffer[indc];
    buffer[indc]=0;
    indc=(indc+1)%N;
    sem_post(&s);
    sem_post(&sp);
  }
  pthread_exit(NULL);
}
