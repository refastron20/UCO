/*** ejercicio3.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
	Analizador léxico de pseudocódigo
 */
  #include <string.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include "ejercicio3.h"

  int token;
  char* cadenaAux;
  char* comentario = NULL;
  int tamComentario = 0;
  int tamCadena = 0;
  /* función que comprueba si una palabra es reservada*/
  char* minuscula(char *cadena);

  int esReservada(char *cadena);
%}
/* expresión para espacios */
espacio		[ \t\n]
espacios {espacio}+
/* expresión regular para identificadores */
identificador [a-zA-Z](_?[a-zA-Z0-9])*
/* expresión regular para números */
numero [0-9]+(\.[0-9]*)?|[0-9](\.[0-9]*)?e[0-9]+

palabra [a-zA-Z0-9]*_*[a-zA-Z0-9]*_*

operador :=|\+|-|\*|\/|__mod|\*\*|\|\||<|<=|>|>=|==|<>|\.o\.|\.y\.|\.no\.

%x ESTADO_COMENTARIO ESTADO_CADENA
%%
{espacios} {;}
{identificador} {
                  cadenaAux=minuscula(yytext);
                  token = esReservada(cadenaAux);
                  if(token!=-1){
                    fprintf(yyout,"\n Palabra reservada: <%s> --> token %d\n", yytext,token);
                  }else{
                    fprintf(yyout,"\n Identificador: <%s> --> token %d\n", yytext, IDENTIFICADOR);
                  }
                }
"'"               {
                  BEGIN ESTADO_CADENA;
                  cadenaAux = malloc(sizeof(char));
                }
<ESTADO_CADENA>"'" {
                    fprintf(yyout,"\n Cadena: <%s> --> token %d\n", cadenaAux, CADENA);
                    cadenaAux = NULL;
                    tamCadena = 0;
                    BEGIN 0;
                  }
<ESTADO_CADENA>.|\n     {
                    tamCadena++;
                    cadenaAux = realloc(cadenaAux, tamCadena*sizeof(char));
                    cadenaAux[tamCadena-1]=yytext[0];
                  }
<ESTADO_CADENA>"\\'"  {
                    tamCadena++;
                    cadenaAux = realloc(cadenaAux, tamCadena*sizeof(char));
                    cadenaAux[tamCadena-1]=yytext[1];
                  }

{numero}        {
                  fprintf(yyout,"\n Número: <%s> --> token %d\n", yytext, NUMERO);
                }
{palabra}       {
                  fprintf(yyout,"\n error: Identificador no válido\n");
                }
[0-9]*,[0-9]*   {
                  fprintf(yyout,"\n error: Número no válido\n");
                }
{operador}      {
                  if(strcmp(yytext,":=")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, ASIGNACION);
                  }
                  if(strcmp(yytext,"+")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, SUMA);
                  }
                  if(strcmp(yytext,"-")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, RESTA);
                  }
                  if(strcmp(yytext,"*")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, PRODUCTO);
                  }
                  if(strcmp(yytext,"/")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, DIVISION);
                  }
                  if(strcmp(yytext,"__mod")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, MODULO);
                  }
                  if(strcmp(yytext,"**")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, POTENCIA);
                  }
                  if(strcmp(yytext,"||")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, CONCATENACION);
                  }
                  if(strcmp(yytext,"<")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, MENOR_QUE);
                  }
                  if(strcmp(yytext,"<=")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, MENOR_IGUAL_QUE);
                  }
                  if(strcmp(yytext,">")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, MAYOR_QUE);
                  }
                  if(strcmp(yytext,">=")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, MAYOR_IGUAL_QUE);
                  }
                  if(strcmp(yytext,"==")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, IGUAL);
                  }
                  if(strcmp(yytext,"<>")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, DISTINTO);
                  }
                  if(strcmp(yytext,".o.")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, DISYUNCION_LOGICA);
                  }
                  if(strcmp(yytext,".y.")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, CONJUNCION_LOGICA);
                  }
                  if(strcmp(yytext,".no.")==0){
                    fprintf(yyout,"\n Operador: <%s> --> token %d\n", yytext, NEGACION_LOGICA);
                  }
                }
; {
  fprintf(yyout,"\n Fin de sentencia: <%s> --> token %d\n", yytext, FIN_SENTENCIA);
}
\( {
  fprintf(yyout,"\n Paréntesis inicial: <%s> --> token %d\n", yytext, PARENTESIS_INICIAL);
}
\) {
  fprintf(yyout,"\n Paréntesis final: <%s> --> token %d\n", yytext, PARENTESIS_FINAL);
}

"(*"    {
        BEGIN ESTADO_COMENTARIO;
        tamComentario = 2;
        comentario = malloc(tamComentario*sizeof(char));
        comentario[0] = '(';
        comentario[1] = '*';
        }

<ESTADO_COMENTARIO>"*)"    {
            BEGIN 0;
            tamComentario += 2;
            comentario = realloc(comentario, tamComentario);
            comentario[tamComentario-1] = ')';
            comentario[tamComentario-2] = '*';
            fprintf(yyout,"\n Comentario: <%s> --> token %d\n", comentario, COMENTARIO);
            tamComentario = 0;
            comentario = NULL;
            }

<ESTADO_COMENTARIO>"(*"(.|\n)    {
                fprintf(yyout,"error: No se pueden anidar comentarios.\n Debería ser así:");
                }
<ESTADO_COMENTARIO>.|\n    {
        tamComentario++;
        comentario = realloc(comentario, tamComentario);
        comentario[tamComentario-1] = yytext[0];
        }

#.*$ {fprintf(yyout,"Comentario de una línea: <%s> --> token %d", yytext, COMENTARIO_LINEA);}


. {fprintf(yyout,"%s<-carácter no reconocido\n",yytext);}
%%

/* Zona de funciones auxiliares */
char* minuscula(char *cadena){
  char *cadena2 = malloc(strlen(cadena)*sizeof(char));
  int i=0;
  for(i=0; i<=strlen(cadena); i++){
    cadena2[i]=tolower(cadena[i]);
  }
  return cadena2;
}

int esReservada(char *cadena){
  char reservadas[][20]={"inicio","fin","leer","escribir","si","entonces","si_no","fin_si","mientras","hacer","fin_mientras",
  "repetir","hasta_que","para","desde","hasta","paso","fin_para"};
  int i=0;
  for(i=0;i<=18;i++){
    if(strcmp(reservadas[i],cadena)==0){
      return 257+i;
    }
  }
  return -1;
}

int main(int argc, char *argv[]){
    yyin=fopen(argv[1],"r");
    yyout=fopen(argv[2],"w");
    yylex();
    return 0;
}
