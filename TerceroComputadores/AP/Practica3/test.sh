#!/usr/bin/env bash
if test -f "./testikj.txt"; then
  rm ./testikj.txt
fi

if test -f "./testijk.txt"; then
  rm ./testijk.txt
fi

if test -f "./testjki.txt"; then
  rm ./testjki.txt
fi

for i in 2 4 8 16 32 64; do
  echo "Bucle(ijk) con $i hilos"
  echo "$(./practica3-ijk-bucle-externo $i)" >> testijk.txt
  echo "Bucle(ikj) con $i hilos"
  echo "$(./practica3-ikj-bucle-externo $i)" >> testikj.txt
  echo "Bucle(ijk) con $i hilos"
  echo "$(./practica3-jki-bucle-interno $i)" >> testjki.txt
done
