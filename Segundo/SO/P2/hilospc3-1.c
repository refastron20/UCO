#include <pthread.h>//biblioteca para hilos
#include <semaphore.h>//biblioteca para semáforos
#include <time.h>//biblioteca para la semilla de números pseudoaleatorios
#include <stdlib.h>//biblioteca para usar rand() y srand()
#include <stdio.h>// biblioteca para imprimir por pantalla

#define ITER 100 //variable para la cantidad de números pseudoaleatorios a generar
#define N 5 //tamaño de buffer
sem_t s; //semáforo para la sección crítica
sem_t sp; //semáforo para el productor, tendrá los huecos libres del buffer
sem_t sc; //semáforo para el consumidor, tendrá los huecos ocupados del buffer
int sump=0; //suma del productor
int sumc=0; //suma del consumidor
int num;//variable que guardará los números pseudoaleatoriosvpara introducirlos en el buffer y hacer la suma del consumidor
int indp=0;//índice para el productor
int indc=0;//índice para el consumidor
int buff[N]; //buffer de N valores

int main(void){
  pthread_t P1,C1; //se declaran los hilos
  void *Productor();//declaración de la función productor
  void *Consumidor();//declraración de la función consumidor
  srand(time(NULL)); //se inicializa la semilla para los números pseudoaleatorios
  int status;//Variable que comprueba el status con el que sale el hilo si hay error

  sem_init(&s, 0, 1);//se inicia el semáforo para la sección crítica
  sem_init(&sp, 0, N);//se inicia con el tamaño del buffer
  sem_init(&sc,0, 0);//se inicia a 0 pues en un primer momento el buffer está vacio, no hay números que leer

  if((status=pthread_create(&P1, NULL, Productor, NULL))!=0){
      exit(status);
  }//inicializado del hilo productor

  if((status=pthread_create(&C1, NULL, Consumidor, NULL))!=0){
    exit(status);
  }//inicializado del hilo consumidor

  pthread_join(P1, NULL);//recogida del hilo productor
  pthread_join(C1, NULL);//recogida del hilo consumidor
  printf("la suma del productor es:%d\n",sump );//muestra la suma del productor
  printf("la suma del consumidor es:%d\n",sumc );//muestra la suma del consumidor
}

void *Productor(){
  for (int i = 0; i < ITER; i++) {//bucle para la creación números pseudoaleatorios
    num=rand()%1001;//producción del número aleatorio
    sem_wait(&sp);//se resta uno al semáforo de tamaño del buffer, si es <0 se bloquea pues no hay huecos libres
    sem_wait(&s);//semáforo de sección crítica
    printf("El nuevo numero es: %d\n",num);//muestra el último número generado
    sump+=num;//hace la suma y la guarda en la variable de suma del productor
    buff[indp]=num;//guarda en el buffer el nuevo valor
    indp=(indp+1)%N;//se aumenta el índice del productor
    sem_post(&s);//semáforo de sección crítica
    sem_post(&sc);//se suma uno a sc pues ya habría uno o mas espacio en el buffer
  }
  pthread_exit(NULL);//salida del hilo
}

void *Consumidor(){
  for (int i = 0; i < ITER; i++) {//bucle para la suma de números pseudoaleatorios
    sem_wait(&sc);//el consumidor esperará a que haya huecos en el buffer para extraerlos
    sem_wait(&s);//semáforo de sección crítica
    sumc+=buff[indc];//se suma el último hueco rellenado del buffer
    buff[indc]=0;//se le da un valor nulo a éste
    indc=(indc+1)%N;//se aumenta el índice del buffer para vaciar la siguiente posición
    sem_post(&s);//semáforo de sección crítica
    sem_post(&sp);//se aumenta en uno sp pues quedarían uno o más huecos libres para rellenar en el buffer
  }
  pthread_exit(NULL);//salida del hilo
}
