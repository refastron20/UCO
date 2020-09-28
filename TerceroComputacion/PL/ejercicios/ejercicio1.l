/*** ejercicio1.l ***/

/*** Zona de las declaraciones o definiciones ***/
%{
   /* Descripción
	El analizador léxico cambia los números enteros por reales
 */
%}

%%
[0-9]*\.[0-9]* {fprintf(yyout, "%s",yytext);}
[0-9]* {fprintf(yyout, "%s.0", yytext);}
%%

/****Zona de funciones auxiliares ***/

extern FILE *yyin, *yyout;

int main(int argc, char *argv[]){
    switch(argc)
    {
    case 2: 
        yyin=fopen(argv[1],"r");
        break;
    case 3:
        yyin=fopen(argv[1],"r");
        yyout=fopen(argv[2],"w");
    }
    yylex();
    return 0;
}
