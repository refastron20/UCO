#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include<sys/time.h>

/* --------------------------------------------------------------------------------------

 Envía una cadena al servidor que puede ser "DAY", "TIME" o "DAYTIME" y le responde con el día, la hora o ambos.

---------------------------------------------------------------------------------------- */

int main ( )
{

		/*----------------------------------------------------
			Descriptor del socket y buffer para datos
		-----------------------------------------------------*/
		int Socket_Cliente;
		char Datos[320];

   	/* -----------------------------------------------------
   		Información del Servidor
   	-----------------------------------------------------*/
   	struct sockaddr_in Servidor;
   	socklen_t Longitud_Servidor;


   	/* --------------------------------------------------
			Se abre el socket cliente
		---------------------------------------------------*/
		Socket_Cliente = socket (AF_INET, SOCK_DGRAM, 0);
		if (Socket_Cliente == -1)
		{
			printf ("No se puede abrir el socket cliente\n");
    			exit (-1);
		}

 		/*---------------------------------------------------------------------
			Necesitamos una estructura con la información del Servidor
			para poder solicitarle un servicio.
   		----------------------------------------------------------------------*/
		Servidor.sin_family = AF_INET;
		Servidor.sin_port = htons(2000);
		Servidor.sin_addr.s_addr =  inet_addr("127.0.0.1");
  	Longitud_Servidor = sizeof(Servidor);


		/*------------------------------------------------------------------------
			Se pide una cadena y se imprime lo que se envió
		------------------------------------------------------------------------ */
		fflush(stdin);
    fgets(Datos, sizeof(Datos), stdin);
		strtok(Datos,"\n");
   	printf ("Envio %s\n", Datos);


		/*-----------------------------------------------------------------------
			Se envía mensaje al Servidor
		-----------------------------------------------------------------------*/
		int enviado = sendto (Socket_Cliente, Datos, sizeof(Datos), 0,
			(struct sockaddr *) &Servidor, Longitud_Servidor);

   	if (enviado < 0)
    	{
			printf("Error al solicitar el servicio\n");
		}
    	else
		{

		/*----------------------------------------------------------------------
			Esperamos la respuesta del Servidor
			----------------------------------------------------------------------- */
			int recibido = recvfrom (Socket_Cliente, Datos, sizeof(Datos), 0,
			(struct sockaddr *) &Servidor, &Longitud_Servidor);

   		if (recibido > 0)
      		printf ("Leido %s\n", Datos);
   		else
      		printf ("Error al leer del servidor\n");

		}

		close(Socket_Cliente);

	return 0;
}
