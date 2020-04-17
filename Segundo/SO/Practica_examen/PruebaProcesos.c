#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hijo1();
void hijo2();
void hijo3();

int main(){
  key_t key ;
  key = ftok("p1ej1.c",1);
  int shmid ;
  if((shmid=shmget(key,100*sizeof(int),IPC_CREAT | 0700))==-1){
    printf("No se pudo reservar memoria\n" );
    exit(-1);
  }

  int *vector;
  vector= (int *)shmat(shmid, NULL, 0);

  if(fork()){
    for (int i = 0; i < 10; i++){
      vector[i]=0;
    }
  }else{
    hijo1();
    exit(0);
  }
  if(!fork()){
    hijo2();
    exit(0);
  }
  if(!fork()){
    hijo3();
    exit(0);
  }
  int status;
  for (int i = 0; i < 3; ++i){
	pid_t pid = wait(&status);
	printf("\nEL hijo %d terminó con status %d\n", pid, WEXITSTATUS(status));
	}
  shmdt(vector);
  shmctl(shmid, IPC_RMID, NULL);
}

void hijo1(){
  srand(time(NULL));
  key_t key = ftok("p1ej1.c",1);
  int shmid ;
  if((shmid=shmget(key, 100*sizeof(int), IPC_CREAT| 0700))==-1)
    exit(-1);

  int *vector;
  vector=shmat(shmid, NULL, 0);

  for(int j=0; j<3; j++){
    for (int i = 0; i < 10; i++) {
      vector[i]=rand()%11;
    }
    sleep(5);
  }

  shmdt(vector);
}

void hijo2(){
  int suma=0;
  key_t key;
  key = ftok("p1ej1.c",1);
  int shmid;
  if ((shmid=shmget(key, 100*sizeof(int), IPC_CREAT | 0700))==-1)
    exit(-1);
  int *vector;
  vector =shmat(shmid, NULL, 0);

  sleep(6);
  for(int j=0; j<3; j++){
    suma=0;
    for (int i = 0; i < 10; i++) {
      suma+=vector[i];
    }
    printf("la suma es %d\n", suma);
    sleep(5);
  }
  shmdt(vector);
}

void hijo3(){
  key_t key;
  key= ftok("p1ej1.c",1);
  int shmid;
  if ((shmid=shmget(key, 100*sizeof(int), IPC_CREAT))==-1)
    exit(-1);
  int *vector;
  vector =shmat(shmid, NULL, 0);

  sleep(7);
  for(int j=0; j<3; j++){
    for (int i = 0; i < 10; i++) {
      printf("Vector[%d]=%d ",i,vector[i] );
    }
    printf("\n");
    sleep(5);
  }
  shmdt(vector);
}
