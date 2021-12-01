CC = g++ -std=c++11
exe_file = assign4
$(exe_file): bats.o driver.o empty.o game.o gold.o pit.o room.o wumpus.o
	$(CC) bats.o driver.o empty.o game.o gold.o pit.o room.o wumpus.o -o $(exe_file)
bats.o: bats.cpp
	$(CC) -c bats.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp
empty.o: empty.cpp
	$(CC) -c empty.cpp
game.o: game.cpp
	$(CC) -c game.cpp
gold.o: gold.cpp
	$(CC) -c gold.cpp
pit.o: pit.cpp
	$(CC) -c pit.cpp
room.o: room.cpp
	$(CC) -c room.cpp
wumpus.o: wumpus.cpp
	$(CC) -c wumpus.cpp
clean:
	rm -f *.out *.o $(exe_file)
