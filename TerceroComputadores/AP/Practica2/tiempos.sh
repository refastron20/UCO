#!/usr/bin/env bash
#if test -f "./testikj.txt"; then
#  rm ./testikj.txt
#fi

#if test -f "./testijk.txt"; then
#  rm ./testijk.txt
#fi

#echo "Practica 1"
#echo "$(./Practica1-ikj)" | grep -o -e "[0-9]*\.*[0-9]*" > testikj.txt
echo "$(./Practica1-ijk)" | grep -o -e "[0-9]*\.*[0-9]*" > testijk.txt

#for i in 2 4 6 8 16; do
#  echo "Practica 2 (ikj) con $i hilos"
#  echo "$(./Practica2-ikj $i)" | grep -o -e "[0-9]*\.*[0-9]*" >> testikj.txt
#done

for i in 4 6 8 16; do
  echo "Practica 2 (ijk) con $i hilos"
  echo "$(./Practica2-ijk $i)" | grep -o -e "[0-9]*\.*[0-9]*" >> testijk.txt
done
