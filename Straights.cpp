#include "Straights.h"
#include <iostream>

Straights::Straights() {
	deck_ = new Deck();
	invitePlayers();
}

void Straights::invitePlayers() {
	for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
		std::cout << "Is player " << (i+1) << " a human(h) or a computer(c)?";
		std::string input = "";
		std::cin >> input;
		assert(input == "c" || input == "C" || input == "H" || input == "h");

		players_[i] = new Player(input);
	}
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		int seed = atoi(argv[1]);
		srand48(seed);
	}  

	Straights *straightsGame = new Straights();
}