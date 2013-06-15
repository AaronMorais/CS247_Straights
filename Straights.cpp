#include "Straights.h"
#include <iostream>

Straights::Straights() {
	deck_ = new Deck();
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		int seed = atoi(argv[1]);
		srand48(seed);
	}  

	Straights *straightsGame = new Straights();
}