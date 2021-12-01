CC = g++ -std=c++11
exe_file = crazy8
$(exe_file): crazy8_driver.o card.o deck.o hand.o player.o game.o
	$(CC) crazy8_driver.o card.o deck.o hand.o player.o game.o -o $(exe_file)
crazy8_driver.o: crazy8_driver.cpp
	$(CC) -c crazy8_driver.cpp
card.o: card.cpp
	$(CC) -c card.cpp
deck.o: deck.cpp
	$(CC) -c deck.cpp
hand.o: hand.cpp
	$(CC) -c hand.cpp
player.o: player.cpp
	$(CC) -c player.cpp
game.o: game.cpp
	$(CC) -c game.cpp
clean:
	rm -f *.out *.o $(exe_file)
