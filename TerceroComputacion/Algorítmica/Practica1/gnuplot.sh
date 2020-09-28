#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoquicksort.eps"
set key right bottom
set xlabel "N"
set ylabel "Tiempo"
plot 'tiempos.txt' using 1:2 t "Tiempo real frente a N" , 'tiempos.txt' using 1:3 t "Tiempo estimado frente a N" w l
_end_
