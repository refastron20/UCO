#!/bin/bash

if [ -z $1 ]; then
echo "Debe introducir un fichero como argumento"
exit -1
fi

for x in $(ls -a ~ | grep '^\..*$'); do

  echo " $(echo $x | wc -c ) $(basename $x)" >> fich.tmp

done
cat fich.tmp | sort -k1 -n | sed -re 's/.* (.*)/\1/'

rm -f fich.tmp

if [ -f $1 ]; then
  echo "===="
  echo "El fichero a procesar es $1"
  cat $1 | sed -r '/^$/d' > $1.sinLineasVacias
  echo "El fichero sin lı́neas vacı́as se ha guardado en $1.sinLineasVacias"
  echo "===="
else
  echo "No existe el fichero introducido"
fi

ps | sed -rn '2,$ s/ *([0-9]*) .* (.*) (.*)/PID: "\1" Hora: "\2" Ejecutable: "\3"/p'
