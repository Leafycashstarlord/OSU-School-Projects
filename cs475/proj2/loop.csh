#!/bin/bash

for t in 1 2 4 8
do
    echo NUMT = $t
    for s in 5 10 100 200 300 400 500 1000 1500 2000
    do
        echo NUMS = $s
        g++   proj2.cpp -o prog -lm -fopenmp
        ./prog $t $s
    done
done