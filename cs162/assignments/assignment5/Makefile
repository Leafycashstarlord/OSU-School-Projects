CC = g++ -std=c++11
exe_file = assign5
$(exe_file): asign5_driver.o node.o llist.o
	$(CC) asign5_driver.o node.o llist.o -o $(exe_file)
asin5_driver.o: asign5_driver.cpp
	$(CC) -c asign5_driver.cpp
node.o: node.cpp
	$(CC) -c node.cpp
llist.o: llist.cpp
	$(CC) -c llist.cpp
clean:
	rm -f *.out *.o $(exe_file)
