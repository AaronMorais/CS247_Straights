CXX = g++

CXXFLAGS = -g -Wall -MMD
OBJECTS = main.o Straights.o Player.o Table.o Command.o Card.o ComputerPlayer.o HumanPlayer.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
clean: 
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
-include ${DEPENDS}