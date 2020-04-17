#!/bin/bash
if [ $# -lt 1 ]; then
  echo "No ha introducido argumentos"
  exit 1
elif [ ! -d $1 ]; then
  echo "Debe introducir un directorio como primer argumento"
  exit 1
else

  if [ -z $2 ]; then
    umbral1=10000
  else
    umbral1=$2
  fi

  if [ -z $3 ]; then
    umbral2=100000
  else
    umbral2=$3
  fi

  if [ -d pequenos ]; then
    echo "Las carpetas de salida ya existen, se procede a borrarlas..."
    rm -rf pequenos
  fi
  echo "Creando las carpetas pequenos. medianos y grandes..."
  mkdir pequenos
  echo "Copiando los archivos..."
  for x in $(find $1 -type f -size -$umbral1'c'); do
    cp $x pequenos
  done


  if [ -d grandes ]; then
    rm -rf grandes
  fi

  mkdir grandes

  for x in $(find $1 -type f -size +$umbral2'c'); do
    cp $x grandes
  done

  if [ -d medianos ]; then
    rm -rf medianos
  fi

  mkdir medianos
  if [ $umbral1 -gt 0 ]; then
      let "umbral1 = $umbral1 - 1"
  fi

  let "umbral2 = $umbral2 + 1"

  for x in $(find $1 -type f -size +$umbral1'c' -size -$umbral2'c'); do
    cp $x medianos
  done
fi
