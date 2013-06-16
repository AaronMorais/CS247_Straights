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
	//game over cases here
	//reshuffle deck cases here as well
	while(true) {
		for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
			int currentPlayerIndex = gameOrder[i];
			if(i==0) {
				std::cout << "A new round begins. It's player " << (currentPlayerIndex+1) << "'s turn to play." << std::endl; 
			}
			if(players_[currentPlayerIndex]->isHuman()) {
				humanTurn(currentPlayerIndex);
			} else {
				robotTurn(currentPlayerIndex);
			}
		}
	}
}

//WHAT IF THEY HAVE NO CARDS LEFT???
//FIX removing cards!
void Straights::humanTurn(int playerIndex) {
	std::cout << "Cards on the table:" << std::endl;

	std::cout << "Clubs: ";
	printCardVectorRanks(tableClubs_);

	std::cout << "Diamonds: ";
	printCardVectorRanks(tableDiamonds_);

	std::cout << "Hearts: ";
	printCardVectorRanks(tableHearts_);

	std::cout << "Spades: ";
	printCardVectorRanks(tableSpades_);

	std::vector<Card> currentHand = players_[playerIndex]->currentHand();
	std::cout << "Your hand: ";
	printCardVector(currentHand);

	std::vector<Card> legalPlaysInHand = getLegalPlays(currentHand);
	std::cout << "Legal plays: ";
	printCardVector(legalPlaysInHand);

	bool turnComplete = false;
	while(!turnComplete) {
		std::string command = humanInput();
		if(command == "play") {
			Card card = *new Card(SUIT_COUNT, RANK_COUNT);
			cin >> card;

			bool validCard = false;
			for(std::vector<Card>::iterator it = legalPlaysInHand.begin(); it != legalPlaysInHand.end(); ++it) {
				if(*it == card) {
					validCard = true;
				}
			}
			if(validCard) {
				playCard(playerIndex, card);
				turnComplete = true;
			} else {
				std::cout << "This is not a legal play." << std::endl;
			}

		} else if(command == "discard") {
			Card card = *new Card(SUIT_COUNT, RANK_COUNT);
			cin >> card;

			if(legalPlaysInHand.size() > 0) {
				std::cout << "You have a legal play. You may not discard." << std::endl;
				turnComplete = false;
			} else {
				bool validCard = false;
				for(std::vector<Card>::iterator it = currentHand.begin(); it != currentHand.end(); ++it) {
					if(*it == card) {
						validCard = true;
					}
				}
				assert(validCard);

				discardCard(playerIndex, card);
				turnComplete = true;
			}

		} else if(command == "deck") {
			for(int i=0; i<CARD_COUNT;i++) {
				if((i%DECK_CARDS_PER_LINE) == 0 && i>0) {
					std::cout << std::endl;
				}
				std::cout << *cards_[i] << " ";
			}
			std::cout << std::endl;

		} else if(command == "quit") {
			exit(0);

		} else if(command == "ragequit") {
			std::cout << "Player " << playerIndex << "ragequits. A computer will now take over.";
			players_[playerIndex]->setHuman(false);
			turnComplete = true;
			robotTurn(playerIndex);
		}
	}
}

std::string Straights::humanInput() {
	std::cout << ">";
	std::string command = "";
	cin >> command;
	assert(command == "play"|| command == "discard"|| command == "deck"|| command == "quit"|| command == "ragequit");
	return command;
}

void Straights::robotTurn(int playerIndex) {
	std::vector<Card> currentHand = players_[playerIndex]->currentHand();
	std::vector<Card> legalPlaysInHand = getLegalPlays(currentHand);
	if(legalPlaysInHand.size() > 0) {
		playCard(playerIndex, legalPlaysInHand.at(0));
	} else {
		playCard(playerIndex, currentHand.at(0));
	}
}

void Straights::playCard(int playerIndex, Card card) {
	players_[playerIndex]->removeCardFromHand(&card);

	Suit suit = card.getSuit();
	std::vector<Card> suitVector;
	if(suit == CLUB) {
		tableClubs_.push_back(card);
	} else if(suit == DIAMOND) {
		tableDiamonds_.push_back(card);
	} else if(suit == HEART) {
		tableHearts_.push_back(card);
	} else if(suit == SPADE) {
		tableSpades_.push_back(card);
	}

	std::cout << "Player " << playerIndex << " plays " << card << ".";
}

void Straights::discardCard(int playerIndex, Card card) {
	players_[playerIndex]->removeCardFromHand(&card);

	int rankInt = card.getRank();
	players_[playerIndex]->addToScore(rankInt);

	std::cout << "Player " << playerIndex << " discards " << card << ".";
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
	//TODO - find out why using -- and ++ was behaving incorrectly
	int left = rankInt - 1;
	int right = rankInt + 1;

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
		int cardRankInt = cardRank;
		if(cardRank == left || cardRank == right) {
			return true;
		}
	}
	return false;
}

void Straights::printCardVectorRanks(std::vector<Card> vector) {
	for(std::vector<Card>::iterator it = vector.begin(); it != vector.end(); ++it) {
	    std::cout << it->getRank() << " ";
	}
	std::cout << std::endl;
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