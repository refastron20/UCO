#!/bin/bash

#in order to use this script you must clean all the couts in the la1 program except the average test and train errors.

files=("sin" "quake" "parkinsons");
layers=("1" "1" "1");
neurons=("2" "2" "2");

rm testVAndF.csv;
echo "Dataset, Nº iterations, Layers, Nº neurons, eta, mu, Validation Ratio, Decrement Factor, ,Average test error, Average train error" >> testVAndF.csv

#first we test the xor apart with F=1 and F=2
echo "xor ,1000, 1, 8, 0.1, 0.9, 0.0, 1, , $(./la1 -t ../../datasetsPr1IMC/dat/train_xor.dat -T ../../datasetsPr1IMC/dat/test_xor.dat -i 1000 -l 1 -h 8 -e 0.1 -m 0.9 -v 0.0 -d 1)" >> testVAndF.csv;
echo "xor ,1000, 1, 8, 0.1, 0.9, 0.0, 2, , $(./la1 -t ../../datasetsPr1IMC/dat/train_xor.dat -T ../../datasetsPr1IMC/dat/test_xor.dat -i 1000 -l 1 -h 8 -e 0.1 -m 0.9 -v 0.0 -d 2)" >> testVAndF.csv;

#then we try the rest with convinations of v and F
for (( n = 0; n < 3; n++ )); do
  for v in 0.0 0.15 0.25
   do
    for F in 1 2
     do
        echo "${files[n]}";
        echo "${files[n]} ,1000, ${layers[n]}, ${neurons[n]}, 0.1, 0.9, $v, $F, , $(./la1 -t ../../datasetsPr1IMC/dat/train_${files[n]}.dat -T ../../datasetsPr1IMC/dat/test_${files[n]}.dat -i 1000 -l ${layers[n]} -h ${neurons[n]} -e 0.1 -m 0.9 -v $v -d $F)" >> testVAndF.csv;
    done
  done
done
