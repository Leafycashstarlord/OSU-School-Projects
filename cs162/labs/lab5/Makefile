CC = g++ -std=c++11
exe_file = lab5profdemo
$(exe_file): lab5_driver.o lab5.o
	$(CC) lab5_driver.o lab5.o -o $(exe_file)
lab5_driver.o: lab5_driver.cpp
	$(CC) -c lab5_driver.cpp
lab5.o: lab5.cpp
	$(CC) -c lab5.cpp
clean:
	rm -f *.out *.o $(exe_file)
