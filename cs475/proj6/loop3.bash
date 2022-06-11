#!/bin/bash

for b in  32 64 128 256
do
        for k in 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288
        do
                g++ -o third third.cpp /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp -DLOCAL_SIZE=$b -DNMB=$k
                ./third
        done
done