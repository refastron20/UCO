#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
  char aux[50]/*aux2[50]*/;
  printf("[PADRE]:Introduzca una palabra:\n");
  fgets(aux,50,stdin);
  printf("CADENA1: %s\n", atoi(strtok(aux,";")));
  printf("CADENA2 %s\n", atoi(strtok(NULL, ";")));
}
