#!/bin/bash
cant=$(find . -maxdepth 1 -type f | wc -l)
echo "El número de archivos en la carpeta actual es $cant"
echo "$(users |tr " " "\n" | uniq)"
read -t 5 -p "¿Qué carácter quieres contar? " caracter
if [ -z $caracter ]; then
  caracter=a
fi

for x in $(find .)
do
	echo "$(basename $x)"
done | grep "$caracter" -o | wc -l > fichero.temp
echo "El carácter $caracter aparece $(cat fichero.temp) veces en nombres de ficheros o carpetas contenidos en la carpeta actual"
rm -f fichero.temp
