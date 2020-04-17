
# ********** EJERCICIO 2 **********

#Script que recibe el fichero 'peliculas.txt' y realiza las siguientes operaciones utilizando 'sed':
	# Elimina las líneas vacías y los subrayados (===).
	# Presenta el título de la película como "Título: xxx" (se recomienda procesarlo al final).
	# Fecha de estreno como "|-> Fecha de estreno: xxx".
	# Director como "|-> Director: xxx".
	# Reparto como "|-> Reparto: xxx".
	# Duración como "|-> Duración: xxx"
	
#Autora: Irene Casares Rodríguez



#!/bin/bash
echo -e "\n"



# ----------------------------------
#      CONTROL DE ARGUMENTOS
# ----------------------------------

if [ $# -ne 1 ]
then
	echo "ERROR: Debe introducir ./ejercicio2.sh <nombre_fichero.txt>"
	echo -e "\n"
	exit 1
fi

if [ ! -f "$1" ]
then	
	echo "$1 no es un fichero."
	exit 1
fi



# ----------------------------------
#          PROCESAMIENTO
# ----------------------------------

cat $1 | sed -e '/^$/d' | sed -r -e '/==+/d' | sed -r -e 's/(\(.*\/.*\/.*\)) (.+)/|-> Fecha de estreno: \1/' | sed -r -e 's/Dirigida por (.+)$/|-> Director: \1/' | sed -r -e 's/Reparto: (.+)/|-> Reparto: \1/' | sed -r -e 's/([[:digit:]]hr [[:digit:]]*min)/|-> Duración: \1/' | sed -r -e '/^ +.+/d' | sed -r -e 's/(^[^(|)].*)/Título: \1/'

echo -e "\n"

# sed -e '/^$/d'
	# Borra las líneas vacías que hay entre cada película.

# sed -r -e '/==+/d'
	# Borra las líneas que contengan los caracteres '===='
	
# sed -r -e 's/(\(.*\/.*\/.*\)) (.+)/|-> Fecha estreno: \1/'
	# "(10/03/2017)" se sustituye por "|-> Fecha estreno: (10/03/2017)"

# sed -r -e 's/Dirigida por (.+)$/|-> Director: \1/'
	# "Dirigida por Gabe Polsky" se sustituye por "|-> Director: Gabe Polsky"

# sed -r -e 's/Reparto: (.+)/|-> Reparto: \1/'
	# "Reparto: Marta Etura, Elvira Minguez, Nene..." se sustituye por "|-> Reparto: Marta Etura, Elvira Minguez, Nene..."

# sed -r -e 's/([[:digit:]]hr [[:digit:]]*min)/|-> Duración: \1/'
	# "1hr 33min" se sustituye por "|-> Duración: 1hr 33min"
	
# sed -r -e '/^ +.+/d'
	# Borra las líneas que comienzan por espacio (toda la sinopsis)

# sed -r -e 's/(^[^(|)].*)/Título: \1/'
	# "Red Army" se sustituye por "Título: Red Army"
	
