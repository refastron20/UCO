
# ********** EJERCICIO 4 **********

#Script que recibe dos argumentos:
	# Primer argumento: fichero de texto con direcciones IP
	# Segundo argumento: número de segundos que deben pasar antes de dar por muerto el servidor
#Hace 'ping' a cada una de las direcciones (mandando un solo 'ping') y las imprime en orden según lo que tardan en contestar. Si la máquina a la que manda el 'ping' no está activa, el comando 'ping' devolverá un código de error distinto de cero al sistema operativo.

#Autora: Irene Casares Rodríguez



#!/bin/bash
echo -e "\n"

# ----------------------------------
#      CONTROL DE ARGUMENTOS
# ----------------------------------

if [ $# -ne 2 ]
then
	echo "ERROR: Debe introducir ./ejercicio4.sh <nombre_file_IP> <segundos>"
	echo -e "\n"
	exit 1
fi

if [ ! -f $1 ]
then
	echo "$1 no es un fichero"
	echo -e "\n"
	exit 1
fi

if [ $2 -lt 1 ]
then
	echo "El número de segundos debe ser mayor o igual que 1"
	echo -e "\n"
	exit 1
fi 

# ----------------------------------
#          PROCESAMIENTO
# ----------------------------------

leido=$(mktemp)
respuesta=$(mktemp)
noRespuesta=$(mktemp)

for x in $(cat $1)
do
	ping -W $2 -c 1 $x > $leido #El resultado de ping lo guardamos en el fichero 'leído' porque nos hará falta en caso de que tenga éxito
	# ping:
	#	-W $2  -->  permite indicar el número de segundos ($2) a esperar para recibir respuesta
	#	-c 1  -->  número de bloques que se envían. Ponemos 1 porque para mandar un 'ping' debemos mandar un único bloque a cada IP
	
	if [ $? -eq 0 ] #Si 'ping' ha tenido éxito
	then
		cat $leido | sed -n -r -e 's/(.+from )(.+)(:.+ )(time=)(.+)( ms)/La IP \2 ha tardado \5 milisegundos/p' >> $respuesta 
		#'sed' obtiene el tiempo que ha tardado en responder y la IP, y lo guardamos en el fichero 'respuesta'
	
	else #Si 'ping' no ha tenido éxito
		echo "La IP $x no respondió tras $2 segundos" >> $noRespuesta
		#En este caso no es necesario hacer 'sed' porque tenemos la IP en $x y los segundos en $2, lo cual guardamos en el fichero 'noRespuesta'
	fi
done
sort -n -k5 $respuesta # 'sort' ordena el fichero 'respuesta' de menor a mayor (-n) según la columna 5 (milisegundos)
cat $noRespuesta #Imprimimos las IP que no han respondido a tiempo

#Borramos los ficheros temporales
rm $leido
rm $respuesta
rm $noRespuesta

echo -e "\n"
		
		
	
	
	
	
	
	
	
	
	
