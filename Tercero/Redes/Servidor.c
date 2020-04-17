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
}Cliente;

void manejador(int signum);
void salirCliente(int socket, fd_set * readfds, int * numClientes, Cliente arrayClientes[]);
int buscarUsuario(char *usuario,char *contrasena);



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
                                    numClientes++;
                                    FD_SET(new_sd,&readfds);

                                    strcpy(buffer, "Bienvenido a Dominó online\n");

                                    send(new_sd,buffer,sizeof(buffer),0);

                                    /*for(j=0; j<(numClientes-1);j++){

                                        bzero(buffer,sizeof(buffer));
                                        sprintf(buffer, "Nuevo Cliente conectado: %d\n",new_sd);
                                        send(arrayClientes[j],buffer,sizeof(buffer),0);
                                    }*/
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
                            //Mensajes que se quieran mandar a los clientes (implementar)

                        }
                        else{
                            bzero(buffer,sizeof(buffer));

                            recibidos = recv(i,buffer,sizeof(buffer),0);

                            if(recibidos > 0){

															for (int j = 0; j < numClientes; j++) {
																if (arrayClientes[j].nCliente==i) {
																	AuxSocket=j;
																}
															}

                              sscanf(buffer,"%s %s\n",cadena1,cadena2);
															if(arrayClientes[AuxSocket].estado<1){
																if (strcmp(cadena1,"USUARIO")==0) {
																	if(buscarUsuario(cadena2, pass)==1){
																		strcpy(arrayClientes[AuxSocket].nomUser,cadena2);
																		strcpy(arrayClientes[AuxSocket].passUser,pass);
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"Usuario registrado, introduzca su contraseña.\n");
																		send(i,buffer,sizeof(buffer),0);
																	}else{
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"Usuario no registrado.\n");
																		send(i,buffer,sizeof(buffer),0);
																	}
																}else if (strcmp(cadena1, "PASSWORD")==0) {
																	if ((strcmp(arrayClientes[AuxSocket].nomUser,"NULL")==0)) {
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"Tiene que introducir su usuario.\n");
																		send(i,buffer,sizeof(buffer),0);
																	}else if((strcmp(cadena2,arrayClientes[AuxSocket].passUser)==0)){
																		arrayClientes[AuxSocket].estado=1;
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"Ha iniciado sesión\n");
																		send(i,buffer,sizeof(buffer),0);
																	}else{
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"contraseña incorrecta\n");
																		send(i,buffer,sizeof(buffer),0);
																	}
																}else{
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"Comando equivocado\n");
																	send(i,buffer,sizeof(buffer),0);
																}
															}else if(arrayClientes[AuxSocket].estado==1){
																if(strcmp(cadena1,"INICIAR-PARTIDA")==0) {
																	for (int j = 0; j < numClientes; j++) {
																		if (arrayClientes[j].estado==2) {
																			arrayClientes[j].estado=3;
																			arrayClientes[AuxSocket].estado=3;
																			bzero(buffer,sizeof(buffer));
																			sprintf(buffer,"Ha encontrado partida con %s\n",arrayClientes[AuxSocket].nomUser );
																			send(arrayClientes[j].nCliente,buffer,sizeof(buffer),0);
																			bzero(buffer,sizeof(buffer));
																			sprintf(buffer,"x Ha encontrado partida con %s\n",arrayClientes[j].nomUser );
																			send(arrayClientes[AuxSocket].nCliente,buffer,sizeof(buffer),0);
																			j=numClientes;
																		}
																	}
																	if(arrayClientes[AuxSocket].estado<3){
																		arrayClientes[AuxSocket].estado=2;
																		bzero(buffer,sizeof(buffer));
																		strcpy(buffer,"Ahora mismo no hay jugadores con los que jugar, se unirá a una partida en cuanto haya alguno\n");
																		send(i,buffer,sizeof(buffer),0);
																	}
																	//INICIAR LA PARTIDA

																}else{
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"Comando equivocado\n");
																	send(i,buffer,sizeof(buffer),0);
																}
															}else if(arrayClientes[AuxSocket].estado==3){
																if(strcmp(cadena1,"PASO-TURNO")==0){
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"Has pasado turno\n");
																	send(i,buffer,sizeof(buffer),0);
																}else if(strcmp(cadena1,"COLOCAR-FICHA")==0){
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"has colocado ficha\n");
																	send(i,buffer,sizeof(buffer),0);
																}else if(strcmp(cadena1,"ROBAR-FICHA\n")==0){
																	bzero(buffer,sizeof(buffer));
																	strcpy(buffer,"has robado ficha\n");
																	send(i,buffer,sizeof(buffer),0);
																}
															}else if(strcmp(cadena1,"SALIR\n")==0) {
																salirCliente(i,&readfds,&numClientes,arrayClientes);
															}

                            }
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0)
                            {
                                printf("El socket %d, ha introducido ctrl+c\n", i);
                                //Eliminar ese socket
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

    char buffer[250];
    int j;

    close(socket);
    FD_CLR(socket,readfds);

    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j].nCliente == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j].nCliente = arrayClientes[j+1].nCliente);

    (*numClientes)--;

    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);

    for(j=0; j<(*numClientes); j++)
        if(arrayClientes[j].nCliente != socket)
            send(arrayClientes[j].nCliente,buffer,sizeof(buffer),0);


}


void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);

    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
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
