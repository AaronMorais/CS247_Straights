all: straights

straights: Straights.cpp Straights.h Player.o Table.o Command.o Card.o ComputerPlayer.o HumanPlayer.o
	g++ Straights.cpp Player.o Table.o Command.o Card.o ComputerPlayer.o HumanPlayer.o -o straights

ComputerPlayer.o: ComputerPlayer.cpp ComputerPlayer.h Player.o
	g++ -c ComputerPlayer.cpp

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h Player.o
	g++ -c HumanPlayer.cpp

Player.o: Player.cpp Player.h Card.o Table.o
	g++ -c Player.cpp

Table.o: Table.cpp Table.h Card.o
	g++ -c Table.cpp

Command.o: Command.cpp Command.h Card.o
	g++ -c Command.cpp

Card.o: Card.cpp Card.h
	g++ -c Card.cpp

clean:
	rm -f straights Player.o Card.o Table.o Command.o