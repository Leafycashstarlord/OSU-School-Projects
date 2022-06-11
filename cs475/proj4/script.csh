#!/bin/bash

for i in 1000 10000 50000 100000 250000 500000 1000000 2000000 4000000 6000000 8000000
do
  g++ -std=c++11 -fopenmp -lm -DARRAYSIZE=$i -o proj4 proj4.cpp
  ./proj4
done