/*** ejercicio2.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
	El analizador léxico cuenta el número de veces que aparece una palabra dada por línea de comandos en un fichero especificado por línea de comandos
 */
#include <string.h>
int numPalabras=0;
int numCoincidencias=0;
char palabra[50];
%}
/**/
%%
[a-z]*[áéíóú]*[a-z]*[ñ]*[a-z]*[áéíóú]*[a-z]* |
[A-Z]*[ÁÉÍÓÚ]*[A-Z]*[Ñ]*[A-Z]*[ÁÉÍÓÚ]*[A-Z]* |
[A-Z]*[a-z]*[áéíóú]*[a-z]*[ñ]*[a-z]*[áéíóú]*[a-z]*  {numPalabras++;if(strcmp(palabra,yytext)==0){numCoincidencias++;}}
.|\n {;}
%%

/****Zona de funciones auxiliares ***/
#include <string.h>
extern FILE *yyin;


int main(int argc, char *argv[]){
    yyin=fopen(argv[1],"r");
    strcpy(palabra, argv[2]);
    yylex();
    printf("El fichero contiene %d palabras.\n", numPalabras);
    printf("Numero de veces que aparece la palabra <%s>: %d \n", palabra, numCoincidencias);
    return 0;
}
