#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#include "Domino.h"


#define MSG_SIZE 250
#define MAX_CLIENTS 30

/*
 * El servidor ofrece el servicio del domino
*/

typedef struct Cliente{
		int nCliente;
		char nomUser[50];
		char passUser[50];
		int estado;//0:sin registrar,1:registrado,2:buscando partida,3:en partida
		int turno;
		struct ficha *fichas;
		int oponente;
		int nPartida;
}Cliente;

void manejador(int signum);
void salirCliente(int socket, fd_set * readfds, int * numClientes, Cliente arrayClientes[]);
int buscarUsuario(char *usuario,char *contrasena);
int registrarUsuario(char *cadena);
void cerrarPartida(struct mesa *mesas[],struct ficha *monton[],struct Cliente arrayClientes[],int cliente1,int cliente2,int nClientes,int *partida);


int main ( )
{

	/*----------------------------------------------------
		Descriptor del socket y buffer de datos
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE], cadena1[MSG_SIZE], cadena2[MSG_SIZE], pass[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    Cliente arrayClientes[MAX_CLIENTS];
    int numClientes = 0;
    //contadores
    int i,j;
		int recibidos;

		int AuxSocket;

		struct ficha *monton[MAX_CLIENTS/2];
		struct mesa *mesas[MAX_CLIENTS/2];
		int partida=0;
		int ganador;

		int noLogin=0;

    int on;




	/* --------------------------------------------------
		Se abre el socket
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);
	}

    // Activaremos una propiedad del socket que permite que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permite en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habría que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on=1;
    setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));



	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  INADDR_ANY;

	if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}


   	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el
		tamaño de su estructura, el resto de información (familia, puerto,
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
		from_len = sizeof (from);


		if(listen(sd,1) == -1){
			perror("Error en la operación de listen");
			exit(1);
		}

    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);


    //Capturamos la señal SIGINT (Ctrl+c)
    signal(SIGINT,manejador);

	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
		while(1){

            //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)

            auxfds = readfds;

            salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);

            if(salida > 0){


                for(i=0; i<FD_SETSIZE; i++){

                    //Buscamos el socket por el que se ha establecido la comunicación
                    if(FD_ISSET(i, &auxfds)) {

                        if( i == sd){

                            if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                                perror("Error aceptando peticiones");
                            }
                            else
                            {
                                if(numClientes < MAX_CLIENTS){
                                    arrayClientes[numClientes].nCliente = new_sd;
																		strcpy(arrayClientes[numClientes].nomUser,"NULL");
																		arrayClientes[numClientes].estado=0;
																		arrayClientes[numClientes].nPartida=-1;
                                    numClientes++;
                                    FD_SET(new_sd,&readfds);

                                    strcpy(buffer, "Bienvenido a Dominó online\n");

                                    send(new_sd,buffer,sizeof(buffer),0);

                                }
                                else
                                {
                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"Demasiados clientes conectados\n");
                                    send(new_sd,buffer,sizeof(buffer),0);
                                    close(new_sd);
                                }

                            }


                        }
                        else if (i == 0){
                            //Se ha introducido información de teclado
                            bzero(buffer, sizeof(buffer));
                            fgets(buffer, sizeof(buffer),stdin);

                            //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                            if(strcmp(buffer,"SALIR\n") == 0){

                                for (j = 0; j < numClientes; j++){
                                    send(arrayClientes[j].nCliente, "Desconexion servidor\n", sizeof("Desconexion servidor\n"),0);
                                    close(arrayClientes[j].nCliente);
                                    FD_CLR(arrayClientes[j].nCliente,&readfds);
                                }
                                    close(sd);
                                    exit(-1);
                            }
                        }
                        else{
                            bzero(buffer,sizeof(buffer));

                            recibidos = recv(i,buffer,sizeof(buffer),0);
														for (int j = 0; j < numClientes; j++) {
															if (arrayClientes[j].nCliente==i) {
																AuxSocket=j;
															}
														}
                            if(recibidos > 0){

                              sscanf(buffer,"%s %s\n",cadena1,cadena2);
															if(arrayClientes[AuxSocket].estado<1){
																if (strcmp(cadena1,"USUARIO")==0) {
																	for (int j = 0; j < numClientes; j++) {
																		if (strcmp(arrayClientes[j].nomUser,cadena2)==0) {
																			noLogin=1;
																		}
																	}
																	if (noLogin==1) {
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"-ERR. Ya hay un usuario activo con ese nombre.\n");
																		send(i,buffer,sizeof(buffer),0);
																	}else{
																		if(buscarUsuario(cadena2, pass)==1){
																			strcpy(arrayClientes[AuxSocket].nomUser,cadena2);
																			strcpy(arrayClientes[AuxSocket].passUser,pass);
																			bzero(buffer,sizeof(buffer));
																			strcpy(buffer,"+OK. Usuario registrado, introduzca su contraseña.\n");
																			send(i,buffer,sizeof(buffer),0);
																		}else{
																			bzero(buffer,sizeof(buffer));
																			strcpy(buffer,"-ERR. Usuario no registrado.\n");
																			send(i,buffer,sizeof(buffer),0);
																		}
																	}
																}else if (strcmp(cadena1, "PASSWORD")==0) {
																	if ((strcmp(arrayClientes[AuxSocket].nomUser,"NULL")==0)) {
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"-ERR. Tiene que introducir su usuario.\n");
																		send(i,buffer,sizeof(buffer),0);
																	}else if((strcmp(cadena2,arrayClientes[AuxSocket].passUser)==0)){
																		arrayClientes[AuxSocket].estado=1;
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"+OK. Ha iniciado sesión\n");
																		send(i,buffer,sizeof(buffer),0);
																	}else{
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"-ERR. Contraseña incorrecta\n");
																		send(i,buffer,sizeof(buffer),0);
																	}
																}else if(strcmp(cadena1,"REGISTER")==0){

																	char nomUser[50],pass[50],nombre[50],apellido[50],ciudad[50],escribir[250];
																	sscanf(buffer,"%s -u %s -p %s -d %s %s -c %s",cadena1,nomUser,pass,nombre,apellido,ciudad);
																	if (buscarUsuario(nomUser,pass)==1) {
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"-ERR. Nombre de usuario no disponible\n");
																		send(i,buffer,sizeof(buffer),0);
																	}else{
																		bzero(escribir,sizeof(escribir));
																		strcat(escribir,nomUser);
																		strcat(escribir," ");
																		strcat(escribir,pass);
																		strcat(escribir," ");
																		strcat(escribir,nombre);
																		strcat(escribir," ");
																		strcat(escribir,apellido);
																		strcat(escribir," ");
																		strcat(escribir,ciudad);
																		strcat(escribir,"\n");
																		if (registrarUsuario(escribir)==1) {
																			bzero(buffer,sizeof(buffer));
																			strcpy(buffer,"+OK. Se ha registrado correctamente, ya puede iniciar sesión\n");
																			send(i,buffer,sizeof(buffer),0);
																		}else{
																			bzero(buffer,sizeof(buffer));
																			strcpy(buffer,"-ERR. No ha podido registrarse\n");
																			send(i,buffer,sizeof(buffer),0);
																		}
																	}
																}else{
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"-ERR. Comando equivocado\n");
																	send(i,buffer,sizeof(buffer),0);
																}
															}else if(arrayClientes[AuxSocket].estado==1){
																if(strcmp(cadena1,"INICIAR-PARTIDA")==0) {
																	for(int j = 0; j < numClientes; j++) {
																		if(arrayClientes[j].estado==2){
																			//guardamos el oponente y el numero de partida para despues
																			arrayClientes[AuxSocket].oponente=j;
																			arrayClientes[j].oponente=AuxSocket;
																			arrayClientes[AuxSocket].nPartida=arrayClientes[j].nPartida=partida;
																			arrayClientes[AuxSocket].estado=arrayClientes[j].estado=3;
																			//Creamos la partida
																			mesas[partida]=reserva_memoria_mesa();
																			monton[partida]=crear_monton();
																			rellenar_jugadores(&arrayClientes[AuxSocket].fichas,&arrayClientes[j].fichas,&monton[partida]);
																			if (empezar_turno(&mesas[partida],&arrayClientes[AuxSocket].fichas,&arrayClientes[j].fichas)==1) {
																				arrayClientes[AuxSocket].turno=1;
																				arrayClientes[j].turno=0;
																				//enviamos el mensaje de confirmación a los clientes junto con sus fichas y la mesa
																				bzero(buffer,sizeof(buffer));
																				sprintf(buffer,"+OK. Ha encontrado partida con %s y es tu turno\n",arrayClientes[j].nomUser);
																				send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																				bzero(buffer,sizeof(buffer));
																				sprintf(buffer,"+OK. Ha encontrado partida con %s y es su turno\n",arrayClientes[AuxSocket].nomUser);
																				send(arrayClientes[j].nCliente,buffer,sizeof(buffer),0);
																			}else{
																				arrayClientes[AuxSocket].turno=0;
																				arrayClientes[j].turno=1;
																				//enviamos el mensaje de confirmación a los clientes junto con sus fichas y la mesa
																				bzero(buffer,sizeof(buffer));
																				sprintf(buffer,"+OK. Ha encontrado partida con %s y  es su turno\n",arrayClientes[j].nomUser);
																				send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																				bzero(buffer,sizeof(buffer));
																				sprintf(buffer,"+OK. Ha encontrado partida con %s y es tu turno\n",arrayClientes[AuxSocket].nomUser);
																				send(arrayClientes[j].nCliente,buffer,sizeof(buffer),0);
																			}
																			bzero(buffer,sizeof(buffer));
																			strcpy(buffer,imprimir_mesa(&mesas[arrayClientes[AuxSocket].nPartida]));
																			send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																			send(arrayClientes[j].nCliente,buffer,sizeof(buffer),0);
																			bzero(buffer,sizeof(buffer));
																			strcpy(buffer,imprimir_vector_fichas(&arrayClientes[AuxSocket].fichas));
																			send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																			bzero(buffer,sizeof(buffer));
																			strcpy(buffer,imprimir_vector_fichas(&arrayClientes[j].fichas));
																			send(arrayClientes[j].nCliente,buffer,sizeof(buffer),0);
																			//Incremento el numero de partida
																			partida++;
																			j=numClientes;
																		}
																	}
																	if(arrayClientes[AuxSocket].nPartida==-1){
																		arrayClientes[AuxSocket].estado=2;
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"-ERR. Ahora mismo no hay jugadores con los que jugar, se unirá a una partida en cuanto haya alguno\n");
																		send(i,buffer,sizeof(buffer),0);
																	}
																}else{
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"-ERR. Comando equivocado\n");
																	send(i,buffer,sizeof(buffer),0);
																}
															}else if(arrayClientes[AuxSocket].estado==3 && arrayClientes[AuxSocket].turno==1){
																if(strcmp(cadena1,"PASO-TURNO")==0){
																	if (pasar_turno(&mesas[arrayClientes[AuxSocket].nPartida],&arrayClientes[AuxSocket].fichas,&monton[arrayClientes[AuxSocket].nPartida])==1) {
																		arrayClientes[AuxSocket].turno=0;
																		arrayClientes[arrayClientes[AuxSocket].oponente].turno=1;
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"+OK. Pasas turno\n");
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"El oponente ha pasado turno, te toca\n");
																		send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																	}else{
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"-ERR. No puedes pasar turno\n");
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																	}
																}else if(strcmp(cadena1,"COLOCAR-FICHA")==0){
																	int izq, der, posicion;
																	char pos[50];
																	sscanf(cadena2,"|%d|%d|,%s",&izq,&der,pos);
																	struct ficha aux;
																	aux.valores[0]=izq;
																	aux.valores[1]=der;
																	if (strcmp(pos,"izquierda")==0) {
																		posicion=1;
																	}else if(strcmp(pos,"derecha")==0){
																		posicion=0;
																	}else{
																		posicion=2;
																	}
																	if (poner_ficha_jugador_a_mesa(&mesas[arrayClientes[AuxSocket].nPartida],&arrayClientes[AuxSocket].fichas,&aux,posicion)==1) {
																		arrayClientes[AuxSocket].turno=0;
																		arrayClientes[arrayClientes[AuxSocket].oponente].turno=1;
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"+OK. Ficha colocada\n");
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,imprimir_mesa(&mesas[arrayClientes[AuxSocket].nPartida]));
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,imprimir_vector_fichas(&arrayClientes[AuxSocket].fichas));
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		bzero(buffer,sizeof(buffer));
																		sprintf(buffer,"El oponente colocó la ficha |%d|%d|, te toca\n",aux.valores[0],aux.valores[1]);
																		send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,imprimir_mesa(&mesas[arrayClientes[AuxSocket].nPartida]));
																		send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																	}else{
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"-ERR. No puedes colocar ficha\n");
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																	}
																}else if(strcmp(cadena1,"ROBAR-FICHA")==0){
																	if (robar_ficha(&mesas[arrayClientes[AuxSocket].nPartida],&arrayClientes[AuxSocket].fichas,&monton[arrayClientes[AuxSocket].nPartida])==1){
																		arrayClientes[AuxSocket].turno=0;
																		arrayClientes[arrayClientes[AuxSocket].oponente].turno=1;
																		bzero(buffer,sizeof(buffer));
																		sprintf(buffer, "+OK. Has robado la ficha: |%d|%d|\n",
																		arrayClientes[AuxSocket].fichas[arrayClientes[AuxSocket].fichas[0].valores[0]].valores[0],
																		arrayClientes[AuxSocket].fichas[arrayClientes[AuxSocket].fichas[0].valores[0]].valores[1] );
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,imprimir_vector_fichas(&arrayClientes[AuxSocket].fichas));
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"El oponente robo ficha, te toca\n");
																		send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																	}else{
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"-ERR. No puedes robar ficha\n");
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																	}
																}else{
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"-ERR. Comando equivocado\n");
																	send(i,buffer,sizeof(buffer),0);
																}
																if ((ganador=hay_ganador(&mesas[arrayClientes[AuxSocket].nPartida],&arrayClientes[AuxSocket].fichas,&arrayClientes[arrayClientes[AuxSocket].oponente].fichas))!=-1) {
																	if (ganador==3) {
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"La partida ha finalizado en empate\n");
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																	}else if(ganador==1){
																		bzero(buffer,sizeof(buffer));
																		sprintf(buffer,"La partida ha finalizado el ganador es %s\n", arrayClientes[AuxSocket].nomUser);
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																	}else{
																		bzero(buffer,sizeof(buffer));
																		sprintf(buffer,"La partida ha finalizado el ganador es %s\n", arrayClientes[arrayClientes[AuxSocket].oponente].nomUser);
																		send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																		send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																	}
																	cerrarPartida(mesas,monton,arrayClientes,AuxSocket,arrayClientes[AuxSocket].oponente,numClientes,&partida);
																}
															}else if(arrayClientes[AuxSocket].estado==3 && arrayClientes[AuxSocket].turno==0){
																bzero(buffer,sizeof(buffer));
																strcpy(buffer,"-ERR. No es tu turno\n");
																send(i,buffer,sizeof(buffer),0);
															}else if(strcmp(cadena1,"SALIR\n")==0) {
																if (arrayClientes[AuxSocket].nPartida!=-1) {
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"El oponente salio de la partida\n");
																	send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																	cerrarPartida(mesas,monton,arrayClientes,AuxSocket,arrayClientes[AuxSocket].oponente,numClientes,&partida);
																}
																salirCliente(i,&readfds,&numClientes,arrayClientes);
															}else{
																bzero(buffer,sizeof(buffer));
																strcpy(buffer,"-ERR. Comando equivocado\n");
																send(i,buffer,sizeof(buffer),0);
															}

                            }
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0)
                            {
                                printf("El socket %d, ha introducido ctrl+c\n", i);
                                //Eliminar ese socket
																if (arrayClientes[AuxSocket].nPartida!=-1) {
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"El oponente salio de la partida\n");
																	send(arrayClientes[arrayClientes[AuxSocket].oponente].nCliente,buffer,sizeof(buffer),0);
																	cerrarPartida(mesas,monton,arrayClientes,AuxSocket,arrayClientes[AuxSocket].oponente,numClientes,&partida);
																}
                                salirCliente(i,&readfds,&numClientes,arrayClientes);
                            }
                        }
                    }
                }
            }
		}

	close(sd);
	return 0;

}

void salirCliente(int socket, fd_set * readfds, int * numClientes, Cliente arrayClientes[]){
    int aux;

    close(socket);
    FD_CLR(socket,readfds);
    //Re-estructurar el array de clientes
    for (int j = 0; j < (*numClientes); j++){
      if (arrayClientes[j].nCliente == socket){
        aux=j;
			}
		}

    for (int j=aux; j < (*numClientes)-1; j++){
      (arrayClientes[j] = arrayClientes[j+1]);
		}
    (*numClientes)--;

		for (int j = 0; j < *numClientes; j++) {
			if (arrayClientes[j].oponente>aux) {
				arrayClientes[j].oponente--;
			}
		}


}


void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);
}

int buscarUsuario(char *usuario,char *contrasena){
	FILE *Usuarios;
	char aux[MSG_SIZE], aux2[MSG_SIZE];
	Usuarios=fopen("Usuarios.txt","r");
	while(fscanf(Usuarios,"%s %s\n",aux,aux2)!=EOF){
		if (strcmp(usuario,aux)==0) {
			fclose(Usuarios);
			strcpy(contrasena,aux2);
			return 1;
		}
	}
	fclose(Usuarios);
	return 0;
}

int registrarUsuario(char *cadena){
	FILE *Usuarios;
	Usuarios=fopen("Usuarios.txt","a");
	if (Usuarios==NULL){
		return 0;
	}else{
		fwrite(cadena,strlen(cadena),1,Usuarios);
	}
	fclose(Usuarios);
	return 1;
}

void cerrarPartida(struct mesa *mesas[],struct ficha *monton[],struct Cliente arrayClientes[],int cliente1,int cliente2,int nClientes,int *partida){
	(*partida)--;
	for (int i = arrayClientes[cliente1].nPartida; i <=*partida; i++) {
		mesas[i]=mesas[i+1];
		monton[i]=monton[i+1];
	}

	for(int i=0;i<nClientes;i++){
		if (arrayClientes[i].nPartida>arrayClientes[cliente1].nPartida) {
			arrayClientes[i].nPartida--;
		}
	}
	mesas[*partida]=NULL;
	monton[*partida]=NULL;
	arrayClientes[cliente1].estado=1;
	arrayClientes[cliente1].nPartida=-1;
	arrayClientes[cliente1].oponente=-1;
	arrayClientes[cliente1].turno=-1;
	arrayClientes[cliente1].fichas=NULL;
	arrayClientes[cliente2].estado=1;
	arrayClientes[cliente2].nPartida=-1;
	arrayClientes[cliente2].oponente=-1;
	arrayClientes[cliente2].turno=-1;
	arrayClientes[cliente2].fichas=NULL;
}
