#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoMatrices.eps"
set key right bottom
set xlabel "N"
set ylabel "Tiempo"
plot 'tiemposMatrices.txt' using 1:2 t "Tiempo real frente a N" , 'tiemposMatrices.txt' using 1:3 t "Tiempo estimado frente a N" w l
_end_
