#!/bin/bash

cat /proc/cpuinfo | sed -rne 's/^model name.*: (.*)/Modelo de procesador: \1/p' | head -1
cat /proc/cpuinfo | sed -rne 's/^cpu MHz.*: (.*)/Megahercios: \1/p' | head -1
cat /proc/cpuinfo | sed -rne 's/^cpu cores.*: (.*)/\1/p' >> fich.tmp
sum=0
for x in $(cat fich.tmp); do
  let sum=$sum+$x
done
rm fich.tmp
echo "Número de hilos máximos de ejecución: $sum"
cat /proc/cpuinfo | sed -rne 's/^cache size.*: (.*)/Tamaño de la caché: \1/p' | head -1
cat /proc/cpuinfo | sed -rne 's/^vendor_id.*: (.*)/ID vendedor: \1/p' | head -1

echo "Puntos de montaje: "
cat /proc/mounts | sed -r 's/^([^ ]+) ([^ ]+) ([^ ]+) .*/->Punto de montaje: \2, Dispositivo:\1, Tipo de dispositivo:\3/'

echo "Particiones y número de bloques:"
cat /proc/partitions | sed -nr '3,$ s/^ *([0-9]+) *([0-9]+) *([0-9]+) (.*)/-> Partición: \4, Número de bloques:\3/p' | sort -k3 -r
