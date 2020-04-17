#!/bin/bash
expresion='[0-9]*'
if [ $# -lt 2 ];then
  echo "Uso del programa: ./repaso1.sh <directorio> <número de bytes>"
  exit -1
elif [ ! -d $1 ]; then
  echo "Uso del programa: ./repaso1.sh <directorio> <número de bytes>"
  exit -1
elif [[ $2 != $expresion ]];then
  echo "Uso del programa: ./repaso1.sh <directorio> <número de bytes>"
  exit -1
fi

nFichC=$(find $1 -name '*.c' | wc -l)
nFichH=$(find $1 -name '*.h' | wc -l)

echo "Hay $nFichC ficheros con extensión .c"
echo "Estos son: "
for x in $(find $1 -name '*.c'); do
  echo "El fichero $(basename $x) con $(cat $x | wc -m) caracteres"
done
echo "Hay $nFichH ficheros con extensión .h"
echo "Estos son: "
for x in $(find $1 -name '*.h'); do
  echo "El fichero $(basename $x) con $(cat $x | wc -m) caracteres"
done

echo -n "¿Desea separarlos en dos carpetas segun el número de bytes? "
read -t5 -p "Sí (S), No (N) " separar

expresion='[Ss]'
if [[ $separar == $expresion ]]; then

  if [ -d pequenos ]; then
    rm -rf pequenos
  fi

  if [ -d grandes ]; then
    rm -rf grandes
  fi

  mkdir pequenos
  mkdir grandes

  for x in $(find $1 -name '*.[ch]'); do
    if [ $(stat -c %s $x) -le $2 ]; then
      cp $x pequenos
    else
      cp $x grandes
    fi
  done
fi

separar='N'
echo -n "¿Desea hacer copia de seguridad? "
read -t5 -p "Sí (S), No (N) " separar

if [[ $separar == $expresion ]]; then

  if [ ! -d ~/Copia ];then
    mkdir ~/Copia
  fi
  mkdir ./Comprimir
  for x in $(find $1 -name '*.[ch]'); do
    cp $x ./Comprimir
  done
  tar -zcf ~/Copia/$(whoami)-$(date +%d-%m-%Y)-$(stat -c %s Comprimir).tar.gz ./Comprimir
  rm -rf Comprimir
fi
