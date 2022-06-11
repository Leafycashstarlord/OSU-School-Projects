#!/bin/bash

for b in 8 16 32 64 128 256 512
do
        for k in 32 64 256 2048 8192
        do
                g++ -o first first.cpp /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp -DLOCAL_SIZE=$b -DNMB=$k
                ./first
        done
done