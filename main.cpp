#include "Straights.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
	int seed = 0;
	if(argc > 1) {
		seed = atoi(argv[1]);
	}  
    srand48(seed);

	Straights *straightsGame = new Straights();
	straightsGame->playGame();
}
