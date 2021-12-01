CC = g++ -std=c++11
exe_file = lab10
$(exe_file): vehicle.o person.o driver.o
	$(CC) vehicle.o person.o driver.o
vehicle.o: vehicle.cpp
	$(CC) -c vehicle.cpp
person.o: person.cpp
	$(CC) -c person.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp
clean:
	rm -f *.out *.o $(exe_file)
