#include "Deck.h"
#include "Card.h"
#include "Card.cpp"
#include <iostream>

int const CARD_COUNT = 52;

Deck::Deck() {
	generateDeck();
	shuffle();
}

void Deck::generateDeck() {
	int cardIndex = 0;
	for(int suitInt=CLUB; suitInt != SUIT_COUNT; suitInt++) {
		for(int rankInt=ACE; rankInt != RANK_COUNT; rankInt++) {
			cards_[cardIndex] = new Card(static_cast<Suit>(suitInt), static_cast<Rank>(rankInt));
			cardIndex++;
		}
	}
}

void Deck::shuffle() {
	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}