#!/bin/bash

if [ -z $1 ] || [ ! -f $1 ]; then
echo "Debe introducir un fichero como argumento"
exit -1
fi
if [ -z $2 ]; then
  echo "Debe introducir como 2º argumento un numero de segundos"
fi

for x in $(cat $1); do
  ping -c 1 -W $2 $x > fich.tmp
  if [ $? -eq 0 ];then
    cat fich.tmp >> ok.tmp
  else
    echo "La IP $x no respondió tras $2 segundos" >> fail.tmp
  fi
done

cat ok.tmp | sed -rn 's/.*[Ff]rom ([0-9]*\.[0-9]*\.[0-9]*\.[0-9]*).*time=([0-9]*\.*[0-9]*).*/La IP \1 respondió en \2 milisegundos/p' | sort -n -k6

cat fail.tmp

rm -f fich.tmp ok.tmp fail.tmp
