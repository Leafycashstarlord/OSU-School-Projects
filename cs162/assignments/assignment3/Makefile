CC = g++ -std=c++11
exe_file = zootycoon
$(exe_file): animal.o tiger.o sealion.o bear.o zootycoon_driver.o zoo.o get_int.o
	$(CC) animal.o tiger.o sealion.o bear.o zootycoon_driver.o zoo.o get_int.o -o $(exe_file)
animal.o: animal.cpp
	$(CC) -c animal.cpp
tiger.o: tiger.cpp
	$(CC) -c tiger.cpp
sealion.o: sealion.cpp
	$(CC) -c sealion.cpp
bear.o: bear.cpp
	$(CC) -c bear.cpp
zootycoon_driver.o: zootycoon_driver.cpp
	$(CC) -c zootycoon_driver.cpp
zoo.o: zoo.cpp
	$(CC) -c zoo.cpp
get_int.o: get_int.cpp
	$(CC) -c get_int.cpp
clean:
	rm -f *.out *.o $(exe_file)
