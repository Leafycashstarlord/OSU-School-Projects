CC = g++ -std=c++11
exe_file = pogwarts
$(exe_file): pogwarts_driver.o pogwarts.o
	$(CC) pogwarts_driver.o pogwarts.o -o $(exe_file)
pogwarts_driver.o: pogwarts_driver.cpp
	$(CC) -c pogwarts_driver.cpp
pogwarts.o: pogwarts.cpp
	$(CC) -c pogwarts.cpp
clean:
	rm -f *.out *.o $(exe_file)
