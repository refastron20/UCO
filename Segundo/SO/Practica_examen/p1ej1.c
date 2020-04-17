#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

void hijo1(){
	int ind, val,shmid;
	key_t key;
	int *vector;
	//compartimos la memoria
	key= ftok("p1ej1.c", 1);
	if((shmid=shmget(key, 100*sizeof(int),0))==-1)
		exit(1);
	vector=(int*)shmat(shmid,NULL,0);
	//se ejecuta 10 veces el bucle que te pide indice y valor a cambiar del vector
	for(int i=0; i<10 ; i++){
	printf("Introduzca el índice de la posición del vector la cual quiere modificar\n");
	scanf("%d", &ind);
	printf("Qué valor quiere introducir\n");
	scanf("%d", &val);
	(vector[ind])=val;
	}
	shmdt(vector);
	exit(7);
}
void hijo2(){
	int shmid;
	key_t key;
	int *vector;
	//se comparte memoria
	key= ftok("p1ej1.c", 1);
	if((shmid=shmget(key, 100*sizeof(int),0))==-1)
		exit(1);
	vector=(int*)shmat(shmid,NULL,0);
	//se cambian 100 valores aleatoriamente
	for(int i=0; i<100;i++){
	(vector[rand()%101])=rand()%101;
	//la función duerme 1 segundo por cada iteración
	sleep(1);
	}
	shmdt(vector);
	exit(7);
}
void hijo3(){
	int shmid;
	key_t key;
	int *vector;
	//se comparte memoria
	key= ftok("p1ej1.c", 1);
	if((shmid=shmget(key, 100*sizeof(int),0))==-1)
		exit(1);
	vector=(int*)shmat(shmid,NULL,0);
	int sum=0;
	//se repite 5 veces la suma de los elementos del vector
	for(int i=0;i<5;i++){
		for (int i = 0; i < 100; ++i)
		{
			sum+=vector[i];
		}
		printf("La suma de los elementos del vector es %d\n",sum );
		sum=0;
		//la función duerme 30 segundos por cada iteración
		sleep(30);
	}
	shmdt(vector);
	exit(7);
}
int main(){
	int shmid, status;
	key_t key;
	int *vector;
	//Creamos la clave
	key=ftok("p1ej1.c",1);
	//reservamos la memoria
	if((shmid=shmget(key,100*sizeof(int),IPC_CREAT | 0700))==-1)
		exit(1);
	//apuntamos el vector a la memoria
	vector=(int*)shmat(shmid,NULL,0);
	//el proceso padre inicializa el vector
	if(fork()){
		srand(time(NULL));
		for (int i = 0; i < 100; ++i)
		{
			vector[i]=rand()%101;
		}
	}
	//los procesos hijos se van metiendo en sus respectivas funciones
	else{
		hijo1();
		exit(0);
	}
	if(!fork()){
		hijo2();
		exit(0);
	}
	if (!fork()){
		hijo3();
		exit(0);
	}
	//por ultimo el padre espera a que terminen los hijos
	for (int i = 0; i < 3; ++i)
	{
	pid_t pid = wait(&status);
	printf("\nEL hijo %d terminó con status %d\n", pid, WEXITSTATUS(status));
	}
	printf("\n");
	//al final se ibera memoria
    shmdt(vector);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;

}
