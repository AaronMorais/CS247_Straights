all: straights

straights: Straights.cpp Straights.h Player.o Table.o Command.o Card.o
	g++ Straights.cpp Player.o Table.o Card.o Command.o -o straights

Player.o: Player.cpp Player.h Card.o
	g++ -c Player.cpp

Table.o: Table.cpp Table.h Card.o
	g++ -c Table.cpp

Command.o: Command.cpp Command.h Card.o
	g++ -c Command.cpp

Card.o: Card.cpp Card.h
	g++ -c Card.cpp

clean:
	rm -f straights Player.o Card.o Table.o Command.o