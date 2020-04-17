#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

#define NCONS 10
#define ITER NCONS
#define N 5

int sump=0;
int sumc=0;
int buffer[N];
int indp=0;
int indc=0;
int consumidores=0;

sem_t s;
sem_t sc;

int main(){
  pthread_t P, C[NCONS];
  int status;
  void *Productor();
  void *Consumidor();
  srand(time(NULL));

  sem_init(&s, 0, 1);
  sem_init(&sc, 0, 1);

  if((status=pthread_create(&P, NULL, (void *) Productor, NULL))!=0){
    exit(status);
  usleep(100);
  int v[NCONS];
}
  for(int i=0; i<NCONS; i++){
    v[i]=i;
    if((status=pthread_create(&C[i], NULL, (void *)Consumidor, (void *) &v[i]))!=0){
      exit(status);
    }
  }

  pthread_join(P, NULL);
  for (int i = 0; i < NCONS; i++) {
    pthread_join(C[i], NULL);
  }

  printf("La suma del Productor es: %d\n",sump );
  printf("La suma del consumidor es: %d\n",sumc );
}


void *Productor(){
  int num;
  //for(int i=0; i<ITER; i++){
    num=rand()%1001;
    sem_wait(&s);
    printf("El nuevo numero es: %d\n", num);
    buffer[indp]=num;
    sump+=num;
    indp=(indp+1)%N;
    sem_post(&s);
  //}
  pthread_exit(NULL);
}

void *Consumidor(void *p){
  int nconsumido;
  int *j=(int *) p;
  //for(int i=ITER; i>=0; i--){
    sem_wait(&sc);
    consumidores++;
    if(consumidores==1)
      sem_wait(&s);
    sem_post(&sc);
    nconsumido=buffer[indc];
    printf("Consumidor nº %d consume buffer[%d]=%d\n",*j  ,indc ,nconsumido);
    sem_wait(&sc);
    consumidores--;
    if(consumidores==0){
      printf("Hola\n" );
      sem_post(&s);
      sumc+=nconsumido;
      buffer[indc]=0;
      indc=(indc+1)%N;
    }
    sem_post(&sc);
  //}
  pthread_exit(NULL);
}
