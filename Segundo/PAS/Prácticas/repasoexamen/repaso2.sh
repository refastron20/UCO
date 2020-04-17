#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Introduzca un fichero"
  exit -1
fi

echo "El fichero $1 tiene: $(cat $1 | wc -l) lineas y $(cat $1 | wc -m) caracteres"
echo "Fecha de creación: $(stat -c %w $1)"
echo "Fecha de última modificación: $(stat -c %y $1)"
echo "Tamaño: $(stat -c %s $1)"
echo "Ruta: $(readlink -f $1)"
