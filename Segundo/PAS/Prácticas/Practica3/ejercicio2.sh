#!/bin/bash
echo "Nombre LongitudUsuario FechaModificacion FechaAcceso Tamano Bloques Permisos Ejecutable"
if [ -z $2 ]; then
  val2=0
else
  val2=$2
fi
val1=$1
for x in $(find $val1 -type f -size +$val2'c')
do
  if [ -x $x ]; then
    eje=1
  else
    eje=0
  fi
  echo "$(basename $x);$(stat -c %U $x | tr -d '\n' | wc -c);$(stat -c %y $x);$(stat -c %X $x);$(stat -c %s $x);$(stat -c %b $x);$(stat -c %A $x);$eje"
done | sort -nk 5 -t ';'
