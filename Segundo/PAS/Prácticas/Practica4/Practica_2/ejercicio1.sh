
# ********** EJERCICIO 1 **********

#Script que recibe el fichero de ejemplo 'peliculas.txt' y ejecuta los comandos adecuados de 'grep' que permiten realizar las siguientes tareas:
	# Mostrar las líneas con la duración de la película (uno o más dígitos al principio de la línea, un espacio y la secuencia "min").
	# Mostrar las líneas que contienen el país de la película (rodeado de guiones, -España-).
	# Mostrar solo los países (sin la línea completa).
	# Contar las películas del 2016 y las del 2017.
	# Mostrar el fichero sin líneas vacías.
	# Mostrar las líneas que empiezan por 'E' (haya o no espacios antes).
	# Mostrar las líneas que contengan una 'd', 'l' o 't', una vocal, y la misma letra de las tres anteriores (Universi'dad').
	# Mostrar las líneas que tengan 8 vocales 'a' o más (mayúsculas o minúsculas y no necesariamente seguidas).
	# Mostrar las líneas que termian con tres puntos (...) y no empiezan por espacio, utilizando el operador de repetición \{...\} o {...}.
	# Utilizar 'sed' para mostrar, entre comillas dobles, las vocales con tilde (mayúsculas o minúsculas).

#Autora: Irene Casares Rodríguez



#!/bin/bash
echo -e "\n"



# ----------------------------------
#      CONTROL DE ARGUMENTOS
# ----------------------------------

if [ $# -ne 1 ]
then
	echo "ERROR: Debe introducir ./ejercicio1.sh <nombre_fichero.txt>"
	echo -e "\n"
	exit 1
fi

if [ ! -f "$1" ] #Si no es un fichero
then
	echo "$1 no es un fichero"
	echo -e "\n"
	exit 1
fi



# ----------------------------------
#          PROCESAMIENTO
# ----------------------------------


echo "***************************************************"
echo -e "\n"
echo "1) Líneas con la duración de las películas:"
echo -e "\n"
cat $1 | sed -r -n -e 's/([[:digit:]]*)(hr) ([[:digit:]]*)(min)/\1\2 \3\4/p' #hora'hr' min'min'
echo -e "\n" 



echo "***************************************************"
echo -e "\n"
echo "2) Líneas con el país de las películas:"
echo -e "\n"
#Se buscan las líneas que tiene algo entre guiones, ya que el país viene entre guiones y se supone que no se utilizarán los guiones para otra cosa.
cat $1 | grep -E '\-.+-'
echo -e "\n"



echo "***************************************************"
echo -e "\n"
echo "3) Sólo el país de las películas:"
echo -e "\n"
#Igual que en el 2, pero con -o solo seleccionamos la parte que coincide. Luego quitamos los guiones, quedándonos sólo con el contenido.
cat $1 | grep -o -E '\-.*\-' | grep -o -E '[^-].+[^-]'
echo -e "\n"



echo "***************************************************"
echo -e "\n"
#No buscamos solo 2016 y 2017 ya que podría aparecer en el argumento. Pasamos el resultado del grep a un wc -l para contar las películas de cada año.
pelis2016=$(cat $1 | grep -E '\([[:digit:]]+/[[:digit:]]+/2016\)' | wc -l)
pelis2017=$(cat $1 | grep -E '\([[:digit:]]+/[[:digit:]]+/2017\)' | wc -l)
echo "4) Hay $pelis2016 películas de 2016 y $pelis2017 películas de 2017"
echo -e "\n"



echo "***************************************************"
echo -e "\n"
echo "5) Eliminar líneas vacías:"
echo -e "\n"
cat $1 | grep '.' #Muestra todas las líneas en las que haya algo; por tanto, obvia las vacías. 
#Otra opción sería grep -v '^$', que mostraría todas las líneas distintas a las vacías (que sean el principio y el final). 
#Con sed sería sed '/./!d' o también sed '/^$/d'.
echo -e "\n"



echo "***************************************************"
echo -e "\n"
echo "6) Líneas que empiezan por la letra E (con o sin espacios antes):"
echo -e "\n"
cat $1 | grep -E '^[[:space:]]*E' #Empieza por ninguno, uno o varios espacios, seguidos de una E
echo -e "\n"



echo "***************************************************"
echo -e "\n"
echo "7) Líneas que contienen 'd', 'l' o 't', una vocal y la misma letra:"
echo -e "\n"
cat $1 | grep -E '([dlt])[aeiou]\1'
echo -e "\n"



echo "***************************************************"
echo -e "\n"
echo "8) Líneas que contienen ocho vocales 'a' o más:"
echo -e "\n"
cat $1 | grep -E -i 'A.*A.*A.*A.*A.*A.*A.*A' 
#Otra opción sería '([Aa].*){8,}'
echo -e "\n"



echo "***************************************************"
echo -e "\n"
echo "9) Líneas que terminan con tres puntos y no empiezan por espacio:"
echo -e "\n"
cat $1 | grep -E '^([^ ]).*(\.{3,3})$'
echo -e "\n"



echo "***************************************************"
echo -e "\n"
echo "10) Mostrar entre comillas las vocales con tilde:"
echo -e "\n"
cat $1 | sed -r -e 's/([áéíóúÁÉÍÓÚ])/"\1"/g' #Con la bandera g se aplica a todo el fichero y no solo a la primera coincidencia.


echo -e "\n"


