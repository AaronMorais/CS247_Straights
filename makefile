CXX = g++

CXXFLAGS = -g `pkg-config gtkmm-2.4 --cflags --libs` -Wall -MMD
OBJECTS = main.o Straights.o Player.o Table.o Command.o Card.o ComputerPlayer.o HumanPlayer.o MainWindow.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
clean: 
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
-include ${DEPENDS}
