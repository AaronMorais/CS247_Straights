#include "Straights.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "limits.h"

Straights::Straights() {
	invitePlayers(); //collects all the human and computer players
	generateDeck(); //generates a deck
	createInitialHands();
	playGame();
}

void Straights::invitePlayers() {
	for(int i=0; i<NUMBER_OF_PLAYERS;i++) { //assigns either human or computer for the number of players
		std::cout << "Is player " << (i+1) << " a human(h) or a computer(c)?\n>";
		char input;
		std::cin >> input;
		assert(input == 'c' || input == 'C' || input == 'H' || input == 'h'); //will only accept human or computer options

		players_[i] = new Player(input, i);
	}
}

void Straights::generateDeck() {
	int cardIndex = 0;
	for(int suitInt=CLUB; suitInt != SUIT_COUNT; suitInt++) { //goes through the 4 suits
		for(int rankInt=ACE; rankInt != RANK_COUNT; rankInt++) { //goes through all ranks
			cards_[cardIndex] = new Card(static_cast<Suit>(suitInt), static_cast<Rank>(rankInt)); //creates the cards based on the suit and ranks
			cardIndex++;
		}
	}
}

void Straights::createInitialHands() {
	shuffleDeck(); //the deck has to be shuffled first

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
	players_[playerIndex]->setLegalPlaysInHand(legalPlaysInHand);
	std::cout << "Legal plays:";
	if(legalPlaysInHand.size() == 0) {
		std::cout << " " << std::endl;
	} else {
		printCardVector(legalPlaysInHand);
	}

	bool turnComplete = false;
	while(!turnComplete) {
		std::cout << ">";
		Command command;
		std::cin >> command;
		if(command.type == PLAY) {

			turnComplete = players_[playerIndex]->humanPlay(command.card, table_);

		} else if(command.type == DISCARD) {

			turnComplete = players_[playerIndex]->humanDiscard(command.card);

		} else if(command.type == DECK) {
			for(int i=0; i<CARD_COUNT;i++) {
				if((i%DECK_CARDS_PER_LINE) == 0 && i>0) {
					std::cout << std::endl;
				}
				std::cout << *cards_[i];
				std::cout << " ";
			}
			std::cout << std::endl;

		} else if(command.type == QUIT) {
			exit(0);

		} else if(command.type == RAGEQUIT) {
			std::cout << "Player " << playerIndex+1 << " ragequits. A computer will now take over." << std::endl;
			players_[playerIndex]->setHuman(false);
			turnComplete = true;
			robotTurn(playerIndex);
		}
	}
}

void Straights::robotTurn(int playerIndex) {
	std::vector<Card> currentHand = players_[playerIndex]->currentHand();
	std::vector<Card> legalPlaysInHand = getLegalPlays(currentHand);
	if(legalPlaysInHand.size() > 0) {
		players_[playerIndex]->playCard(legalPlaysInHand.at(0), table_);
	} else {
		players_[playerIndex]->discardCard(currentHand.at(0));
	}
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
