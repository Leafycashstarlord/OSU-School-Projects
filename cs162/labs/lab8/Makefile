CC = g++ -std=c++11
exe_file = lab8
$(exe_file): try_vector.o
	$(CC) try_vector.o -o $(exe_file)
try_vector.o: try_vector.cpp
	$(CC) -c try_vector.cpp
clean:
	rm -f *.out *.o $(exe_file)
