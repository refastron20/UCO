#include "Domino.h"

struct ficha crear_ficha(int a, int b){//reserva memoria y se crea ficha
	struct ficha nueva;
	nueva.valores[0] = a; //introduzco sus valores
	nueva.valores[1] = b;
	return nueva;
}

struct mesa *reserva_memoria_mesa(){//función para reservar memoria para la estructura mesa
	struct mesa *temp = NULL;
	temp = calloc(1, sizeof(struct mesa));//reserva de memoria inicializada a 0 gracias a calloc
	return temp;
}

void revolver(struct ficha *monton){//función que revuelve todas las fichas
	struct ficha aux[DOMINO];
	bool isFree[DOMINO];
	int j=1,pos;
	srand(time(NULL));

	for (int i = 0; i < DOMINO; i++) {
		isFree[i]=true;
	}
	aux[0]=monton[0];
	while (j<DOMINO) {
		pos=(rand()%28)+1;
		if (isFree[pos]==true) {
			aux[j]=monton[pos];
			j++;
			isFree[pos]=false;
		}
	}
	for (int i = 0; i < DOMINO; i++) {
		monton[i]=aux[i];
	}
}

struct ficha *crear_monton(){
	//parte para crear las fichas
	struct ficha* monton;
	monton = malloc(DOMINO*sizeof(struct ficha));//reservamos memoria para monton donde se almacenaran todas las fichas
	struct ficha aux[DOMINO];
	aux[0].valores[0]=28;
	aux[0].valores[1]=-1;
	int contador=1;
	for(int i=0;i<7;i++){//con estos bucles creo todas las fichas sin repetirme en algunas por ejemplo [1|0] y [0|1]
		for(int j=0;j<=i;j++){
			aux[contador] = crear_ficha(i,j);//esta variable guardara temporalmente la ficha
			contador++;
		}
	}

	revolver(aux);//función que revuelve las fichas
	for (int i = 0; i < DOMINO; i++) {
		monton[i]=aux[i];
	}
	return monton;
}

struct ficha quitar_ficha_jugador(struct ficha ***jugador, int lugar_ficha){//funcion para quitar ficha de un jugador en la posicion deseada
	struct ficha temporal;
	temporal = jugador[0][0][lugar_ficha];//almaceno la ficha buscada para devolverla
	for(int i=lugar_ficha; i < jugador[0][0][0].valores[0]; i++){//con este for reajusto todo el vector en caso de coger una ficha que no sea la última
		jugador[0][0][i] = jugador[0][0][i+1];
	}
	struct ficha *aux;
	aux=malloc( ((jugador[0][0][0].valores[0])*(sizeof(struct ficha))));
	for (int i = 0; i < jugador[0][0][0].valores[0]; i++) {
		aux[i]=jugador[0][0][i];
	}
	aux[0].valores[0]--;
	free(jugador[0][0]);
	jugador[0][0]=aux;
	return temporal;
}

void rellenar_jugadores(struct ficha **jugador1, struct ficha **jugador2, struct ficha **monton){
	jugador1[0]=malloc(8*sizeof(struct ficha));
	struct ficha f;
	f.valores[0]=7;
	f.valores[1]=-1;
	jugador1[0][0]=f;
	for (int i = 1; i < 8; i++) {
		jugador1[0][i]=quitar_ficha_jugador(&monton,1);
	}
	jugador2[0]=malloc(8*sizeof(struct ficha));
	jugador2[0][0]=f;
	for (int i = 8; i < 15; i++) {
		jugador2[0][i-7]=quitar_ficha_jugador(&monton,1);
	}
}

char *imprimir_vector_fichas(struct ficha **jugador){//imprime una ficha
	char texto[250];
	char buffer[50];
	sprintf(texto, "FICHAS ");
	for(int i=0; i<jugador[0][0].valores[0];i++){
		bzero(buffer,sizeof(buffer));
		sprintf(buffer, "|%i|%i|", jugador[0][i+1].valores[0], jugador[0][i+1].valores[1]);
		strcat(texto, buffer);
	}
	bzero(buffer,sizeof(buffer));
	sprintf(buffer, "\n");
	strcat(texto, buffer);
	char *pointer=texto;
	return pointer;
}

void agregar_ficha_mesa(struct mesa ***m, struct ficha *f){//añadimos una ficha a una mesa

	//asignamos espacio para una nueva ficha
	struct ficha *aux;
	aux=malloc(sizeof(struct ficha ) * (m[0][0]->total+1));
	for (int i = 0; i < m[0][0]->total; i++) {
		aux[i]=m[0][0]->fichas[i];
	}
	free(m[0][0]->fichas);
	m[0][0]->fichas=aux;
	//guardamos la ficha f en el espacio creado
	m[0][0]->fichas[m[0][0]->total] = *f;
	//incrementamos el contador de fichas de esta estructura en 1 y actualizamos primero y último
	m[0][0]->total++;
	m[0][0]->primero = &(m[0][0]->fichas[0]);
	m[0][0]->ultimo = &(m[0][0]->fichas[m[0][0]->total-1]);
}

int buscar_doble(struct ficha ***jugador, int valor){//busca la posicion donde se encuentra una ficha
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=0;
	while(!encontrado && i < jugador[0][0][0].valores[0]){//recorremos todas la fichas hasta encontrar la ficha doble o no
		if(jugador[0][0][i].valores[0] == valor && jugador[0][0][i].valores[1] == valor){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}

int buscar_ficha_jugador(struct ficha ***jugador, int valor0, int valor1){//busca una ficha con esos dos valores
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=1;
	while(!encontrado && i < jugador[0][0][0].valores[0]+1){//recorremos todas la fichas hasta encontrar la ficha doble o no
		if((jugador[0][0][i].valores[0] == valor0 && jugador[0][0][i].valores[1] == valor1)||(jugador[0][0][i].valores[0] == valor1 && jugador[0][0][i].valores[1] == valor0)){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}

int empezar_turno(struct mesa **m, struct ficha **jugador1, struct ficha **jugador2){

	//procedemos ha dar turno al jugador con el mayor doble y si no poseen dobles al de número mayor
	struct ficha temporal;
	int encontradoJ1 = -1;
	int encontradoJ2 = -1;
	int buscar = 6;

	while(encontradoJ1 == -1 && encontradoJ2 == -1 && buscar > 0){
		encontradoJ1 = buscar_doble(&jugador1,buscar);
		encontradoJ2 = buscar_doble(&jugador2,buscar);
		buscar--;
	}
	if(encontradoJ1 != -1){
		temporal = quitar_ficha_jugador(&jugador1, encontradoJ1);//le quito la ficha para ponerla en la mesa
		agregar_ficha_mesa(&m,&temporal);
		return 2;

	}else if(encontradoJ2 != -1){
		temporal = quitar_ficha_jugador(&jugador2, encontradoJ2);//le quito la ficha para ponerla en la mesa
		agregar_ficha_mesa(&m,&temporal);
		return 1;
	}else{
		buscar = 6;
		int buscar2;
		while(encontradoJ1 == -1 && encontradoJ2 == -1 && buscar > 0){
			buscar2 = 6;
			while(encontradoJ1 == -1 && encontradoJ2 == -1 && buscar2 > 0){
				encontradoJ1 = buscar_ficha_jugador(&jugador1,buscar,buscar2);
				encontradoJ2 = buscar_ficha_jugador(&jugador2,buscar,buscar2);
				buscar2--;
			}
			buscar--;
		}
		if(encontradoJ1 != -1){
			temporal = quitar_ficha_jugador(&jugador1, encontradoJ1);//le quito la ficha para ponerla en la mesa
			agregar_ficha_mesa(&m,&temporal);
			return 2;
		}else if(encontradoJ2 != -1){
			temporal = quitar_ficha_jugador(&jugador2, encontradoJ2);//le quito la ficha para ponerla en la mesa
			agregar_ficha_mesa(&m,&temporal);
			return 1;
		}else{
			return -1;
		}
	}
}

char *imprimir_mesa(struct mesa **m){//imprime una ficha
	char texto[250];
	char *pointer;
	char buffer[50];
	sprintf(texto, "TABLERO ");

	for(int i=0; i<m[0]->total;i++){
		bzero(buffer,sizeof(buffer));
		sprintf(buffer, "|%i|%i|", m[0]->fichas[i].valores[0], m[0]->fichas[i].valores[1]);
		strcat(texto, buffer);
	}
	bzero(buffer,sizeof(buffer));
	sprintf(buffer, "\n");
	strcat(texto, buffer);
	pointer=texto;
	return pointer;
}

void rotar_ficha(struct ficha *f){ //rota la ficha, es decir, cambia los valores de posición
	int aux;
	aux = f->valores[0];//uso valor auxiliar para no machacar el valor de la ficha dada
	f->valores[0] = f->valores[1];
	f->valores[1] = aux;
}

void agregar_ficha_esquina(struct mesa ***m, struct ficha *f, bool posicion){//agrego ficha en los extremos de la mesa, al principio o al final
	//si posicion es true es en el principio y si es false al final

	//asignamos espacio para una nueva ficha
	struct ficha *aux;
	aux=malloc(sizeof(struct ficha) * (m[0][0]->total+1));
	for (int i = 0; i < m[0][0]->total; i++) {
		aux[i]=m[0][0]->fichas[i];
	}
	free(m[0][0]->fichas);
	m[0][0]->fichas=aux;
	//guardamos la ficha f en el espacio creado
	if(posicion){
		int i = m[0][0]->total;
		while(i > 0){//desplazo toda la mesa uno a la derecha para crear espacio para la nueva ficha
			m[0][0]->fichas[i] = m[0][0]->fichas[i-1];
			i--;
		}
		m[0][0]->fichas[0] = *f;
	}else{
		m[0][0]->fichas[m[0][0]->total] = *f;
	}
	//incrementamos el contador de fichas de esta estructura en 1 y actualizamos primero y último
	m[0][0]->total++;
	m[0][0]->primero = &(m[0][0]->fichas[0]);
	m[0][0]->ultimo = &(m[0][0]->fichas[m[0][0]->total-1]);
}

bool poner_ficha_jugador_a_mesa(struct mesa **m, struct ficha **jugador, struct ficha *ficha, int posicion){
	int valor;
	if(posicion==1){//veo el valor donde quiere poner su ficha
		valor=m[0]->primero->valores[0];
	}else if(posicion==0){
		valor=m[0]->ultimo->valores[1];
	}else{
		return false;
	}

	if(buscar_ficha_jugador(&jugador,ficha->valores[0],ficha->valores[1])==-1){
		return false;
	}

	if((ficha->valores[0]!=valor)&&(ficha->valores[1]!=valor))
		return false;//compruebo que la ficha se puede poner

	int encontrado=buscar_ficha_jugador(&jugador, ficha->valores[0], ficha->valores[1]);
	struct ficha aux;
	aux = quitar_ficha_jugador(&jugador, encontrado);

	if(posicion && m[0]->primero->valores[0] != aux.valores[1]){//compruebo si es necesario girar en la primera posicion
			rotar_ficha(&aux);
	}else if(!posicion && m[0]->ultimo->valores[1] != aux.valores[0]){//compruebo si es necesario girar en la ultima posicion
			rotar_ficha(&aux);
	}
	agregar_ficha_esquina(&m, &aux, posicion);

	return true;
}

int buscar_valor_jugador(struct ficha ***jugador, int valor){//busca la posicion donde se encuentra una ficha
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=1;
	while(!encontrado && i < jugador[0][0][0].valores[0]+1){//recorremos todas la fichas hasta encontrar el valor pedido o no
		if(jugador[0][0][i].valores[0] == valor || jugador[0][0][i].valores[1] == valor){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}

bool pasar_turno(struct mesa **m, struct ficha **jugador, struct ficha **monton){//comprobar si puede pasar turno
	int izq;
	int der;
	izq = m[0]->primero->valores[0];
	der = m[0]->ultimo->valores[1];

	if (monton[0][0].valores[0]!=0) {
		return false;
	}

	if((buscar_valor_jugador(&jugador, izq)==-1)&&(buscar_valor_jugador(&jugador, der)==-1))
		return true;

	return false;
}

bool robar_ficha(struct mesa **m, struct ficha **jugador, struct ficha **monton){
	if (monton[0][0].valores[0]==0) {
		return false;
	}
	int izq;
	int der;
	izq = m[0]->primero->valores[0];
	der = m[0]->ultimo->valores[1];
	if ((buscar_valor_jugador(&jugador, izq)!=-1)||(buscar_valor_jugador(&jugador, der)!=-1)) {
		return false;
	}
	struct ficha *aux;
	aux=malloc( ((jugador[0][0].valores[0]+2)*(sizeof(struct ficha))));
	for (int i = 0; i < jugador[0][0].valores[0]+1; i++) {
		aux[i]=jugador[0][i];
	}
	aux[0].valores[0]++;
	aux[aux[0].valores[0]]=quitar_ficha_jugador(&monton,1);
	free(jugador[0]);
	jugador[0]=aux;
	return true;
}

int buscar_valor_mesa(struct mesa ***m, int valor){//busca la posicion donde se encuentra una ficha
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=0;
	while(!encontrado && i < m[0][0]->total){//recorremos todas la fichas hasta encontrar el valor pedido o no
		if(m[0][0]->fichas[i].valores[0] == valor || m[0][0]->fichas[i].valores[1] == valor){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}

int hay_ganador(struct mesa **m, struct ficha **jugador1, struct ficha **jugador2){

	if(jugador1[0][0].valores[0] == 0)
		return 1;//gana jugador 1
	if(jugador2[0][0].valores[0] == 0)
		return 2;//gana jugador 2

	if(m[0]->primero->valores[0]==m[0]->ultimo->valores[1]){//compruebo valores de las esquinas
		int acumulador=0;
		for(int i=0;i<m[0]->total;i++){
			if(buscar_valor_mesa(&m, m[0]->primero->valores[0])!=-1){
				acumulador++;//funciona rara
			}
		}
		if(acumulador>=7){
			int suma1 = 0;
			int suma2 = 0;
			for(int i=0;i<jugador1[0][0].valores[0];i++){
				suma1=suma1+jugador1[0][i].valores[0]+jugador1[0][i].valores[1];
			}
			for(int i=0;i<jugador2[0][0].valores[0];i++){
				suma2=suma2+jugador2[0][i].valores[0]+jugador2[0][i].valores[1];
			}
			if(suma1>suma2){
				return 1;//gana jugador 1
			}else if(suma1<suma2){
				return 2;//gana jugador 2
			}else{
				return 3;//empate
			}
		}
	}
	return -1;//no gana nadie
}

/*


int buscar_ficha_mesa(struct mesa *m, int valor0, int valor1){//busca la posicion donde se encuentra una ficha
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=0;
	while(!encontrado && i < m->total){//recorremos todas la fichas hasta encontrar la ficha doble o no
		if((m->fichas[i]->valores[0] == valor0 && m->fichas[i]->valores[1] == valor1)||(m->fichas[i]->valores[0] == valor1 && m->fichas[i]->valores[1] == valor0)){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}



struct ficha *consultar_valores(struct mesa *m){//devuelve los valores en los extremos de la mesa
	struct ficha *f = malloc(sizeof(struct ficha));
	f->valores[0] = m->primero->valores[0];//primer valor de la mesa
	f->valores[1] = m->ultimo->valores[1];//ultimo valor de la mesa
	return f;
}


*/
