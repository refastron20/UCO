#!/bin/bash

#in order to use this script you must clean all the couts in the la1 program except the average test and train final errors.

files=("xor" "sin" "quake" "parkinsons");

rm test.csv;
echo "Dataset, Nº iterations, Layers, Nº neurons, eta, mu, Validation Ratio, Decrement Factor, ,Average test error, Average train error" >> test.csv

for (( n = 0; n < 4; n++ )); do
  for l in 1 2
   do
    for h in 2 4 8 16 32 64 100
     do
      for m in 0.9 0.8 0.7 0.5
       do
        echo "${files[n]} ,1000, $l, $h, 0.1, $m, 0.0, 1, , $(./la1 -t ../../datasetsPr1IMC/dat/train_${files[n]}.dat -T ../../datasetsPr1IMC/dat/test_${files[n]}.dat -i 1000 -l $l -h $h -e 0.1 -m $m -v 0.0 -d 1)" >> test.csv;
      done
    done
  done
done
