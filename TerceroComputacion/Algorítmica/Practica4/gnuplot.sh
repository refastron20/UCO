
cat << _end_ | gnuplot
set terminal postscript eps color
set output "avionPoly.eps"
set key right bottom
plot './avion.txt'
_end_
