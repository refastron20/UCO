/*** ejercicio3.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
	Analizador léxico que cuenta el número de cuentas bancarias
 */
#include <string.h>
int numCuentas = 0, numCoincidencias = 0;
char *aux;
char *cadena;
int flag = 0;
%}
espacio [\ ]
cuenta_pais [A-Z]{2,2}
numero_pais [0-9]{2,2}
cuenta_entidad [0-9]{4,4}
cuenta_oficina {cuenta_entidad}
numeros_verificacion [0-9]{2,2}
numeros_finales [0-9]{10,10}
cuenta {cuenta_pais}{numero_pais}{espacio}{cuenta_entidad}{espacio}{cuenta_entidad}{espacio}{numeros_verificacion}{espacio}{numeros_finales}
%%
{cuenta} {
  numCuentas++;
  switch(flag){
    case 1:
      aux = malloc(2*sizeof(char));
      aux[0]=yytext[0];
      aux[1]=yytext[1];
      if(strcmp(cadena,aux)==0){
        numCoincidencias++;
      }
    break;
    case 2:
      aux = malloc(6*sizeof(char));
      aux[0]=yytext[0];
      aux[1]=yytext[1];
      aux[2]=yytext[5];
      aux[3]=yytext[6];
      aux[4]=yytext[7];
      aux[5]=yytext[8];
      if(strcmp(cadena,aux)==0){
        numCoincidencias++;
      }
    break;
    case 3:
      aux = malloc(10*sizeof(char));
      aux[0]=yytext[0];
      aux[1]=yytext[1];
      aux[2]=yytext[5];
      aux[3]=yytext[6];
      aux[4]=yytext[7];
      aux[5]=yytext[8];
      aux[6]=yytext[10];
      aux[7]=yytext[11];
      aux[8]=yytext[12];
      aux[9]=yytext[13];
      if(strcmp(cadena,aux)==0){
        numCoincidencias++;
      }
  }
}
.|\n {;}
%%

/* Zona de funciones auxiliares */


int main(int argc, char *argv[]){
    yyin=fopen(argv[1],"r");
    flag = argc-2;
    switch(flag){
      case 1:
        cadena = malloc(strlen(argv[2])*sizeof(char));
        strcpy(cadena, argv[2]);
      break;
      case 2:
      cadena = malloc((strlen(argv[2])+strlen(argv[3]))*sizeof(char));
      strcpy(cadena, argv[2]);
      strcat(cadena, argv[3]);
      break;
      case 3:
      cadena = malloc((strlen(argv[2])+strlen(argv[3])+strlen(argv[4]))*sizeof(char));
      strcpy(cadena, argv[2]);
      strcat(cadena, argv[3]);
      strcat(cadena, argv[4]);
      break;
    }
    yylex();
    if(flag==0){
      printf("Numero de cuentas: %d\n",numCuentas);
    }else{
      printf("Numero de cuentas de %s: %d\n",argv[2],numCoincidencias);
    }
    return 0;
}
