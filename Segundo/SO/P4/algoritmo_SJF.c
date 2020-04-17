#include <string.h>
#include <stdio.h>


typedef struct Parametros{
    char nombre[10];//Parametros que se introducen
    int t_llegada;
    int t_ejecucion;
    int t_comienzo;//Parametros que se calculan
    int t_finalizacion;
    int t_retorno;
    int t_espera;
} Parametros;


int main(void){
  Parametros p[5];

  //Proceso 1
  strcpy(p[0].nombre,"A");
  p[0].t_llegada=0;
  p[0].t_ejecucion=8;
  p[0].t_comienzo=p[0].t_llegada;
  p[0].t_finalizacion=p[0].t_ejecucion;
  p[0].t_retorno=p[0].t_ejecucion;
  p[0].t_espera=0;
  //Proceso 2
  strcpy(p[0].nombre,"B");
  p[1].t_llegada=1;
  p[1].t_ejecucion=4;
  //Proceso 3
  strcpy(p[0].nombre,"C");
  p[2].t_llegada=2;
  p[2].t_ejecucion=9;
  //Proceso 4
  strcpy(p[0].nombre,"D");
  p[3].t_llegada=3;
  p[3].t_ejecucion=5;
  //Proceso 5
  strcpy(p[0].nombre,"E");
  p[4].t_llegada=4;
  p[4].t_ejecucion=2;

  int ejec=0;
  
  for(int i=0; i<18 ; i++){

    if((p[].t_llegada<p[].t_finalizacion)&&(p[].t_ejecucion<p[].t_ejecucion))){
      ejec=1;
    }
  }
  printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
  printf("-------------------------------------------------------\n");

  for (int i = 0; i < 5; i++) {
    printf("%s\n", );
  }
}
