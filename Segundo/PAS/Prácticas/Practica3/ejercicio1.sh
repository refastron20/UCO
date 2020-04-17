#!/bin/bash

if [ $# -lt 1 -o $# -gt 1 ] ;
then
 echo "No ha introducido bien el argumento"
 exit 1
elif [ -d $1 ];
then
  cant1=$(find $1  -name "*.c" | wc -l)
  cant2=$(find $1  -name "*.h" | wc -l)

  echo "Tenemos $cant1 Ficheros con extensión .c y $cant2 Ficheros con extensión .h"

  for x in $(find $1  -name "*.c" -o -name "*.h")
  do
    echo "El fichero $x tiene $(cat $x|wc -l) lineas y $(cat $x|wc -m) caracteres"
  done | sort -nr -k 8
else
  echo "No existe el directorio"
  exit 1
fi
