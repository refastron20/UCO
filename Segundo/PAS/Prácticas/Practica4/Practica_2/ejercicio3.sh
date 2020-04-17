
# ********** EJERCICIO 3 **********

#Script que recibe un fichero y que utiliza 'grep' y/o 'sed' para lo siguiente:
	# Listar todos los ficheros ocultos de la carpeta personal del usuario ordenados por número de caracteres.
	# Hacer una copia del fichero recibido en la que se eliminan todas las líneas vacías. Su nombre será "FICH.sinLineasVacias", donde FICH es el nombre del fichero introducido. Esto se hará siempre que exista.
	# Listar todos los procesos que el usuario está ejecutando, mostrando el PID, la hora en que se lanzó y el nombre del fichero ejecutable.

#Autora: Irene Casares Rodríguez



#!/bin/bash
echo -e "\n"

# ----------------------------------
#      CONTROL DE ARGUMENTOS
# ----------------------------------

if [ $# -ne 1 ]
then
	echo "ERROR: Debe introducir ./ejercicio3.sh <nombre_fichero.txt>"
	echo -e "\n"
	exit 1
fi



# ----------------------------------
#          PROCESAMIENTO
# ----------------------------------

directorio="/home/$USER"

echo "Listado de archivos ocultos del directorio $directorio"
temp=$(mktemp) # mktemp --> crea fichero o directorio temporal

for x in $(ls -a $directorio) # ls -a  --> muestra todos los ficheros, incluso los ocultos
do
	nomFile=$(basename $x)
	fichOculto=$(echo $nomFile | grep '^\.') #Los ficheros ocultos comienzan por punto (.)
	
	if [[ $fichOculto == $nomFile ]]
	then
		nLineas=$(echo $fichOculto | wc -c)
		echo "$nLineas;$fichOculto" >> $temp
	fi
done
cat $temp | sort -n -k1 | sed -n -e 's/\(.*\);\(.*\)/\2/p' #'sort' ordena de menor a mayor (-n) según la columna 1 (nLineas).
echo -e "\n"



echo "===="
echo -e "\n"
if [ -e $1 ]
then
	if [ -f "$1" ] 
	then
		echo "El fichero a procesar es $1"
		cat $1 | grep '^.' > $1.sinLineasVacias #También podríamos usar sed -e '/^$/d'
		echo "El fichero sin líneas vacías se ha guardado en $1.sinLineasVacias"
		
	else	
		echo "$1 no es un fichero."
	fi
	
else
	echo "El fichero recogido no existe, por lo que no se copiará."
fi
echo -e "\n"



echo "===="
echo -e "\n"
echo "Listado de los procesos ejecutados por el usuario $USER: "
ps -u $USER -o pid,comm | grep '[0-9]\{1,\}' | sed -n -e 's/\([0-9]\{1,\}\) \(.*\)/PID: \"\1\" Ejecutable: \"\2\"/p'

echo -e "\n"
