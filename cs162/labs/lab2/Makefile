CC = g++
exe_file = student_db
$(exe_file): lab2_driver.o lab2.o
	$(CC) lab2_driver.o lab2.o -o $(exe_file)
lab2_driver.o: lab2_driver.cpp
	$(CC) -c lab2_driver.cpp
lab2.o: lab2.cpp
	$(CC) -c lab2.cpp
clean:
	rm -f *.out *.o $(exe_file)
