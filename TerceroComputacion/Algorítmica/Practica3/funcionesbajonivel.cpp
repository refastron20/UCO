#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>

#include "funcionesbajonivel.hpp"


void agregarCerosFinal(char* &c, int nCeros)
{
	int n, numeroCaracteres;
	char *nuevaCadena = NULL;
	int i;

	n = strlen(c);
	numeroCaracteres = n + nCeros;

	nuevaCadena = reservarCadena(numeroCaracteres + 1);

	for(i = 0; i < n; i++) //Se rellena la primera cadena
		nuevaCadena[i] = c[i];

	for(i = n; i < numeroCaracteres; i++) //Se rellena con los ceros al final
		nuevaCadena[i] = '0';
	nuevaCadena[i] = '\0';

	delete [] c; //Se libera la cadena antigua

	c = nuevaCadena;
}



void quitarCerosNoSignificativos(char* &c)
{
	char *aux;
	int l, i = 0;
	int numeroCeros = 0;

	l = strlen(c);
	//Contamos ceros no significativos
	while(c[i] == '0' && i < l)
	{
		i++;
		numeroCeros++;
	}

	//Reservamos nueva cadena
	aux = reservarCadena(l - numeroCeros + 1);

	//Copiamos la cadena sin los ceros no significativos
	for(i = numeroCeros; i < l; i++)
		aux[i - numeroCeros] = c[i];

	aux[l - numeroCeros] = '\0'; //Cerramos la cadena
	delete []c;
	c = aux;
}

char * multiplicarPotencia10(char *c, int potencia)
{
	char *aux;

	aux = reservarCadena(strlen(c) + 1);
	strcpy(aux, c);
	agregarCerosFinal(aux, potencia);
	return aux;
}
