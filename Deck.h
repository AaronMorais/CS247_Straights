#include "Card.h"

class Deck {
public:
	Deck();
private:
	Card *cards_ [52];
	void shuffle();
	void generateDeck();
};