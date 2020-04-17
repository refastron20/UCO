#include <pthread.h>//biblioteca para hilos
#include <semaphore.h>//biblioteca para semáforos
#include <time.h>//biblioteca para la semilla de números pseudoaleatorios
#include <stdlib.h>//biblioteca para usar rand() y srand()
#include <stdio.h>// biblioteca para imprimir por pantalla

#define NPROD 5
#define NCONS 5
#define ITER 100 //variable para la cantidad de números pseudoaleatoriosa generar
#define N 5 //tamaño de buffer
sem_t s; //semáforo para la sección crítica
sem_t sp; //semáforo para el productor, tendrá los huecos libres del buffer
sem_t sc; //semáforo para el consumidor, tendrá los huecos ocupados del buffer
int sump=0; //suma del productor
int sumc=0; //suma del consumidor
int buff[N]; //buffer de N valores
int ind=0;

int main(void){
  pthread_t P[NPROD],C[NCONS]; //se declaran los hilos
  void *Productor();//declaración de la función productor
  void *Consumidor();//declraración de la función consumidor
  srand(time(NULL)); //se inicializa la semilla para los números pseudoaleatorios

  sem_init(&s, 0, 1);//se inicia el semáforo para la sección crítica
  sem_init(&sp, 0, N);//se inicia con el tamaño del buffer
  sem_init(&sc,0, 0);//se inicia a 0 pues en un primer momento el buffer está vacio, no hay números que leer

  for (int i = 0; i < NPROD; i++) {
    pthread_create(&P[i], NULL, Productor, NULL);//inicializado del hilo productor
  }

  for (int i = 0; i < NCONS; i++) {
    pthread_create(&C[i], NULL, Consumidor, NULL);//inicializado del hilo consumidor
  }

  for (int i = 0; i < NPROD; i++) {
    pthread_join(P[i], NULL);//recogida del hilo productor
  }

  for (int i = 0; i < NCONS; i++) {
    pthread_join(C[i], NULL);//recogida del hilo consumidor
  }



  printf("la suma del productor es:%d\n",sump );//muestra la suma del productor
  printf("la suma del consumidor es:%d\n",sumc );//muestra la suma del consumidor
}

void *Productor(){
  int num;
  for (int i = 0; i < ITER; i++) {//bucle para la creación números pseudoaleatorios
    num=rand()%1001;//producción del número aleatorio
    sem_wait(&sp);//se resta uno al semáforo de tamaño del buffer, si es <0 se bloquea pues no hay huecos libres
    sem_wait(&s);//semáforo de sección crítica
    printf("El nuevo numero es: %d\n",num);//muestra el último número generado
    sump+=num;//hace la suma y la guarda en la variable de suma del productor
    printf("La suma del productor es: %d\n",sump );
    buff[ind]=num;//guarda en el buffer el nuevo valor
    printf("Productor:Buffer[%d]:%d \n",ind, buff[ind]);
    ind++;
    sem_post(&s);//semáforo de sección crítica
    sem_post(&sc);//se suma uno a sc pues ya habría uno o mas espacio en el buffer
  }
  pthread_exit(NULL);//salida del hilo
}

void *Consumidor(){
  for (int i = 0; i < ITER; i++) {//bucle para la suma de números pseudoaleatorios
    sem_wait(&sc);//el consumidor esperará a que haya huecos en el buffer para extraerlos
    sem_wait(&s);//semáforo de sección crítica
    sumc+=buff[ind];//se suma el último hueco rellenado del buffer
    printf("La suma del consumidor es: %d\n",sumc );
    printf("Consumidor:Buffer[%d]:%d \n",ind, buff[ind] );
    buff[ind]=0;//se le da un valor nulo a éste
    ind--;//se aumenta el índice del buffer para vaciar la siguiente posición
    sem_post(&s);//semáforo de sección crítica
    sem_post(&sp);//se aumenta en uno sp pues quedarían uno o más huecos libres para rellenar en el buffer
  }
  pthread_exit(NULL);//salida del hilo
}
