#ifndef FUNCIONES_BAJO_NIVEL
#define FUNCIONES_BAJO_NIVEL


//Esta función añade tantos ceros como indica nCeros al final del número almacenado en la cadena c
void agregarCerosFinal(char* &c, int nCeros);

//Esta función añade tantos ceros como indica nCeros al principio del número almacenado en la cadena c
void agregarCerosDelante(std::string &c, int nCeros);

//Esta función elimina todos los ceros que hay al principio del número almacenado en la cadena c
void quitarCerosNoSignificativos(char* &c);

//Esta función devuelve una cadena que contendrá el número resultante de multiplicar el número almacenado en la cadena c por 10 elevado a potencia.
char * multiplicarPotencia10(char *c, int potencia);

#endif
