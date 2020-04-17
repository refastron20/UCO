#!/bin/bash


function mostrar(){
  echo "<ul>" >> $file
  for x in $(find $1 -maxdepth 1) ;do
    if [ -d $x ] && [ $1 != $x ]; then
      echo "<li><strong>$(pwd)/$x</strong></li>" >> $file
      mostrar $x
    elif [ $1 != $x ]; then
      echo "<li>$(pwd)/$x</li>" >> $file
    fi
  done
  echo "</ul>" >> $file
}

if [  -z $1 ]; then
  echo "Debe introducir un directorio"
  exit 1
elif [ -d $1 ]; then
  if [ -f $1.html ]; then
    rm -f $1.html
  fi
  file=$1.html
  echo "Generando el listado de la carpeta $(pwd)/$1 sobre el fichero $file..."
  echo "<html>" >> $file
  echo "<head>" >> $file
  echo "<title>Listado del directorio $1</title>" >> $file
  echo "</head><body>" >> $file
  echo "<style type="text/css">" >> $file
  echo "body { font-family: sans-serif;}" >> $file
  echo "</style>" >> $file
  echo "<h1>Listado del directorio $1</h1>" >> $file

  mostrar $1

  echo "</body>" >> $file
  echo "</html>" >> $file
  echo "Terminado!!!"
else
  echo "Introduzca un directorio válido"
  exit 1
fi
