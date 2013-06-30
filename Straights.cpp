#include "Straights.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "limits.h"

Straights::Straights() {
	invitePlayers();
	generateDeck();
	createInitialHands();
	playGame();
}

void Straights::invitePlayers() {
	for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
		std::cout << "Is player " << (i+1) << " a human(h) or a computer(c)?\n>";
		char input;
		std::cin >> input;
		assert(input == 'c' || input == 'C' || input == 'H' || input == 'h');

		players_[i] = new Player(input);
	}
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

void Straights::createInitialHands() {
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

void Straights::playGame() {
	bool gameOver = false;
	while(!gameOver) {
		int cardsRemaining = CARD_COUNT/NUMBER_OF_PLAYERS; //Assuming hands will be evenly divisible
		std::cout << "A new round begins. It's player " << (gameOrder[0]+1) << "'s turn to play." << std::endl; 
		while(cardsRemaining != 0) {
			for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
				int currentPlayerIndex = gameOrder[i];

				if(players_[currentPlayerIndex]->isHuman()) {
					humanTurn(currentPlayerIndex);
				} else {
					robotTurn(currentPlayerIndex);
				}
			}
			cardsRemaining--;
		}

		int minimumScore = INT_MAX;

		for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
			printRoundEnd(i);

			int score = players_[i]->totalScore();
			if(score >= GAME_OVER_SCORE) {
				gameOver = true;
			}
			if(score < minimumScore) {
				minimumScore = score;
			}
		}

		if(gameOver) {
			for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
				int score = players_[i]->totalScore();
				if(score == minimumScore) {
					std::cout << "Player " << (i+1) << " wins!" << std::endl;
				}
			}
		} else {
			createInitialHands();
			table_.empty();
		}
	}
}

void Straights::humanTurn(int playerIndex) {
	std::cout << table_;

	std::vector<Card> currentHand = players_[playerIndex]->currentHand();
	std::cout << "Your hand:";
	printCardVector(currentHand);

	std::vector<Card> legalPlaysInHand = getLegalPlays(currentHand);
	std::cout << "Legal plays:";
	if(legalPlaysInHand.size() == 0) {
		std::cout << " " << std::endl;
	} else {
		printCardVector(legalPlaysInHand);
	}

	bool turnComplete = false;
	while(!turnComplete) {
		std::string command = humanInput();
		if(command == "play") {
			Card card = *new Card(SUIT_COUNT, RANK_COUNT);
			std::cin >> card;

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
			std::cin >> card;

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
				std::cout << *cards_[i];
				std::cout << " ";
			}
			std::cout << std::endl;

		} else if(command == "quit") {
			exit(0);

		} else if(command == "ragequit") {
			std::cout << "Player " << playerIndex+1 << " ragequits. A computer will now take over." << std::endl;
			players_[playerIndex]->setHuman(false);
			turnComplete = true;
			robotTurn(playerIndex);
		}
	}
}

std::string Straights::humanInput() {
	std::cout << ">";
	std::string command = "";
	std::cin >> command;
	assert(command == "play"|| command == "discard"|| command == "deck"|| command == "quit"|| command == "ragequit");
	return command;
}

void Straights::robotTurn(int playerIndex) {
	std::vector<Card> currentHand = players_[playerIndex]->currentHand();
	std::vector<Card> legalPlaysInHand = getLegalPlays(currentHand);
	if(legalPlaysInHand.size() > 0) {
		playCard(playerIndex, legalPlaysInHand.at(0));
	} else {
		discardCard(playerIndex, currentHand.at(0));
	}
}

void Straights::playCard(int playerIndex, Card card) {
	players_[playerIndex]->removeCardFromHand(card);

	Suit suit = card.getSuit();
	if(suit == CLUB) {
		table_.addClubs(card);
	} else if(suit == DIAMOND) {
		table_.addDiamonds(card);
	} else if(suit == HEART) {
		table_.addHearts(card);
	} else if(suit == SPADE) {
		table_.addSpades(card);
	}

	std::cout << "Player " << playerIndex+1 << " plays " << card << "." << std::endl;
}

void Straights::discardCard(int playerIndex, Card card) {
	players_[playerIndex]->removeCardFromHand(card);
	players_[playerIndex]->addCardToDiscards(card);

	int rankInt = card.getRank() + 1;
	players_[playerIndex]->addToRoundScore(rankInt);

	std::cout << "Player " << playerIndex+1 << " discards " << card << "." <<std::endl;
}

std::vector<Card> Straights::getLegalPlays(std::vector<Card> vector) {
	std::vector<Card> legalPlaysInHand;

	for(std::vector<Card>::iterator it = vector.begin(); it != vector.end(); ++it) {
		if((it->getSuit() == SPADE) && (it->getRank() == SEVEN)) {		
			std::vector<Card> firstMoveHand;
			firstMoveHand.push_back(*it);
			return firstMoveHand;
		}
		if(table_.isLegalCard(*it)) {
			legalPlaysInHand.push_back(*it);
		}
	}
	return legalPlaysInHand;
}

void Straights::printRoundEnd(int playerIndex) {
	Player *player = players_[playerIndex];

	std::cout << "Player " << (playerIndex+1) << "'s discards:";
	if(player->discards().size() == 0) {
		std::cout << " ";
	}
	printCardVector(player->discards());

	std::cout << "Player " << (playerIndex+1) << "'s score: " << player->totalScore() << " + " << player->roundScore();
	std::cout << " = " << (player->totalScore() + player->roundScore()) << std::endl;

	player->addToTotalScore(player->roundScore());
	player->resetRoundScore();
	player->clearDiscards();
}

void Straights::printCardVector(std::vector<Card> vector) {
	int size = vector.size();
	for(std::vector<Card>::size_type i = 0; i != size; i++) {
		std::cout << " ";
	    std::cout << vector[i];
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	int seed = 0;
	if(argc > 1) {
		seed = atoi(argv[1]);
	}  
    srand48(seed);

	Straights *straightsGame = new Straights();
}
