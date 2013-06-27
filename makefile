all: straights

straights: Straights.cpp Straights.h Player.o Card.o
	g++ Straights.cpp Player.o Card.o -o straights

Player.o: Player.h Player.cpp Card.o
	g++ -c Player.cpp

Card.o: Card.cpp Card.h
	g++ -c Card.cpp

clean:
	rm -f straights Player.o Card.o