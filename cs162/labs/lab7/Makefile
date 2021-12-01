CC = g++ -std=c++11
exe_file = lab7
$(exe_file): lab7_driver.o shape.o circle.o rectangle.o square.o
	$(CC) lab7_driver.o shape.o circle.o rectangle.o square.o -o $(exe_file)
lab7_driver.o: lab7_driver.cpp
	$(CC) -c lab7_driver.cpp
shape.o: shape.cpp
	$(CC) -c shape.cpp
circle.o: circle.cpp
	$(CC) -c circle.cpp
rectangle.o: rectangle.cpp
	$(CC) -c rectangle.cpp
square.o: square.cpp
	$(CC) -c square.cpp
clean:
	rm -f *.out *.o $(exe_file)
