#include "Straights.h"
#include <iostream>
#include <vector>
#include <cassert>

Straights::Straights() {
	invitePlayers();
	createInitialHands();
	playGame();
}

void Straights::invitePlayers() {
	for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
		std::cout << "Is player " << (i+1) << " a human(h) or a computer(c)?\n>";
		std::string input = "";
		std::cin >> input;
		assert(input == "c" || input == "C" || input == "H" || input == "h");

		players_[i] = new Player(input);
	}
}

void Straights::playGame() {
	while(true) {
		for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
			int currentPlayerIndex = gameOrder[i];
			if(players_[currentPlayerIndex]->isHuman()) {
				humanTurn(currentPlayerIndex);
			}
		}
		break;
	}
}

void Straights::humanTurn(int playerIndex) {
	std::cout << "Cards on the table:" << std::endl;

	std::cout << "Clubs: ";
	printCardVector(tableClubs_);

	std::cout << "Diamonds: ";
	printCardVector(tableDiamonds_);

	std::cout << "Hearts: ";
	printCardVector(tableHearts_);

	std::cout << "Spades: ";
	printCardVector(tableSpades_);

	std::vector<Card> currentHand = players_[playerIndex]->currentHand();
	std::cout << "Your hand: ";
	printCardVector(currentHand);

	std::vector<Card> legalPlaysInHand = getLegalPlays(currentHand);
	std::cout << "Legal plays: ";
	printCardVector(legalPlaysInHand);
}

std::vector<Card> Straights::getLegalPlays(std::vector<Card> vector) {
	std::vector<Card> legalPlaysInHand;
	for(std::vector<Card>::iterator it = vector.begin(); it != vector.end(); ++it) {
		if(isLegalCard(*it)) {
			legalPlaysInHand.push_back(*it);
		}
	}
	return legalPlaysInHand;
}

bool Straights::isLegalCard(Card card) {
	Suit suit = card.getSuit();
	Rank rank = card.getRank();
	if(rank == SEVEN) {
		return true;
	}
	int rankInt = rank;
	Rank left = static_cast<Rank>(rankInt--);
	Rank right = static_cast<Rank>(rankInt++);

	std::vector<Card> suitVector;
	if(suit == CLUB) {
		suitVector = tableClubs_;
	} else if(suit == DIAMOND) {
		suitVector = tableDiamonds_;
	} else if(suit == HEART) {
		suitVector = tableHearts_;
	} else if(suit == SPADE) {
		suitVector = tableSpades_;
	}
	for(std::vector<Card>::iterator it = suitVector.begin(); it != suitVector.end(); ++it) {
		Rank cardRank = it->getRank();
		if(cardRank == left || cardRank == right) {
			return true;
		}
	}
	return false;
}

void Straights::printCardVector(std::vector<Card> vector) {
	for(std::vector<Card>::iterator it = vector.begin(); it != vector.end(); ++it) {
	    std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void Straights::generateGameOrder(int startingPlayer) {
	int index = 0;
	for(int i = startingPlayer; i<NUMBER_OF_PLAYERS; i++) {
		gameOrder[index] = i;
		index++;
	}
	for(int j=0; j<startingPlayer; j++) {
		gameOrder[index] = j;
		index++;
	}
}

void Straights::createInitialHands() {
	generateDeck();
	shuffleDeck();

	int handSize = CARD_COUNT/NUMBER_OF_PLAYERS; //Assuming hands will be evenly divisible
	int cardIndex = 0;
	int startingPlayer = 0;

	for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
		for(int j=cardIndex; j<(cardIndex+handSize);j++) {
			players_[i]->addCardToHand(*cards_[j]);

			if((cards_[j]->getSuit() == SPADE) && (cards_[j]->getRank() == SEVEN)) {
				startingPlayer = i;
			}
		}
		cardIndex +=handSize;
	}
	generateGameOrder(startingPlayer);
}

void Straights::generateDeck() {
	int cardIndex = 0;
	for(int suitInt=CLUB; suitInt != SUIT_COUNT; suitInt++) {
		for(int rankInt=ACE; rankInt != RANK_COUNT; rankInt++) {
			cards_[cardIndex] = new Card(static_cast<Suit>(suitInt), static_cast<Rank>(rankInt));
			cardIndex++;
		}
	}
}

void Straights::shuffleDeck() {
	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		int seed = atoi(argv[1]);
		srand48(seed);
	}  

	Straights *straightsGame = new Straights();
}