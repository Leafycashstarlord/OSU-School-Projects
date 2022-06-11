#!/bin/csh

foreach t ( 4 )
	g++ -DNUMT=$t proj3.cpp -o proj3 -lm -fopenmp
	./proj3
end
