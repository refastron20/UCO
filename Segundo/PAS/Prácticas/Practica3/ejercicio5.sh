#!/bin/bash
if [ $# == 0 ]; then
  echo "Debe introducir un directorio"
  exit 1
else
  if [ ! -d ~/Copia  ]; then
    mkdir ~/Copia
  fi
  mkdir comprimir
  for x in $*; do
    cp -r $x comprimir
  done
  tar -zcf ~/Copia/copia-$(whoami)-$(date +%s).tar.gz ./comprimir
  rm -rf comprimir
  echo "La copia de seguridad se ha creado correctamente"

  for x in $(find ~/Copia -type f); do
    let segundos=$(date +%s)-$(stat $x -c %Y)
    if [  $segundos -gt 200 ]; then
      echo "borrando $x de $segundos segundos"
      rm $x
    fi
  done
fi
