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
}

void Straights::invitePlayers() {
	for(int i=0; i<NUMBER_OF_PLAYERS;i++) { //assigns either human or computer for the number of players
		std::cout << "Is player " << (i+1) << " a human(h) or a computer(c)?\n>";
		char input;
		std::cin >> input;
		assert(input == 'c' || input == 'C' || input == 'H' || input == 'h'); //will only accept human or computer options
		if(input == 'c' || input == 'C'){
			players_[i] = new ComputerPlayer(i);
		}else{
			players_[i] = new HumanPlayer(i);
		}
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

	for(int i=0; i<NUMBER_OF_PLAYERS;i++) { //goes through each player
		for(int j=cardIndex; j<(cardIndex+handSize);j++) { //only deals out handsize number of cards
			players_[i]->addCardToHand(*cards_[j]); //takes the cards from the deck

			if((cards_[j]->getSuit() == SPADE) && (cards_[j]->getRank() == SEVEN)) {
				startingPlayer = i; //finds the starting player while dealing
			}
		}
		cardIndex +=handSize; //move to the next card index for the next player
	}
	generateGameOrder(startingPlayer); //determines the order of the players
}

void Straights::shuffleDeck() { //given function
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
	for(int i = startingPlayer; i<NUMBER_OF_PLAYERS; i++) { //game order starts with the startingPlayer
		gameOrder[index] = i;
		index++;
	}
	for(int j=0; j<startingPlayer; j++) { //since the game ordering is circular, continue from where the other loop left off
		gameOrder[index] = j;
		index++;
	}
}

void Straights::playGame() {
	bool gameOver = false;
	while(!gameOver) {
		int cardsRemaining = CARD_COUNT/NUMBER_OF_PLAYERS; //Assuming hands will be evenly divisible
		std::cout << "A new round begins. It's player " << (gameOrder[0]+1) << "'s turn to play." << std::endl; 
		while(cardsRemaining != 0) {//cards remaining in hand
			for(int i=0; i<NUMBER_OF_PLAYERS;i++) { //goes through each players turn
				int currentPlayerIndex = gameOrder[i];

				players_[currentPlayerIndex]->setLegalPlays(table_); //the player determines its legal plays based on the table
				if(players_[currentPlayerIndex]->isHuman()) {
					humanTurn(currentPlayerIndex);
				} else {
					robotTurn(currentPlayerIndex);
				}
			}
			cardsRemaining--; //every player has either played a card or discarded
		}

		int minimumScore = INT_MAX;

		for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
			printRoundEnd(i); //print round stats for each player

			int score = players_[i]->totalScore();
			if(score >= GAME_OVER_SCORE) {
				gameOver = true;
			}
			if(score < minimumScore) { //sets minimum score
				minimumScore = score;
			}
		}

		if(gameOver) {
			for(int i=0; i<NUMBER_OF_PLAYERS;i++) {
				int score = players_[i]->totalScore();
				if(score == minimumScore) { //finds the winner by finding a match with the minimum score
					std::cout << "Player " << (i+1) << " wins!" << std::endl;
				}
			}
		} else { //new round need to create new hands and a new table
			createInitialHands();
			table_.empty();
		}
	}
}

void Straights::humanTurn(int playerIndex) {
	std::cout << table_; //the table is first printed out
	//next the player's hand
	std::vector<Card> currentHand = players_[playerIndex]->currentHand();
	std::cout << "Your hand:";
	printCardVector(currentHand);

	std::cout << "Legal plays:";
	if(players_[playerIndex]->legalPlays().size() == 0) { //if there are no legal plays
		std::cout << " " << std::endl;
	} else {
		printCardVector(players_[playerIndex]->legalPlays()); //print the legal plays
	}

	bool turnComplete = false; //invalid moves will result in false
	while(!turnComplete) {
		std::cout << ">";
		Command command;
		std::cin >> command; //reads command
		if(command.type == PLAY) { //human plays a card on the table
			turnComplete = players_[playerIndex]->play(table_, command.card);
		} else if(command.type == DISCARD) { //human discards
			turnComplete = players_[playerIndex]->discard(command.card);
		} else if(command.type == DECK) {
			for(int i=0; i<CARD_COUNT;i++) {
				if((i%DECK_CARDS_PER_LINE) == 0 && i>0) { //new line when the cards per line has been reached
					std::cout << std::endl;
				}
				std::cout << *cards_[i]; //prints out each card
				std::cout << " ";		 //with a space in between
			}
			std::cout << std::endl;
		} else if(command.type == QUIT) {
			exit(0);
		} else if(command.type == RAGEQUIT) {
			std::cout << "Player " << playerIndex+1 << " ragequits. A computer will now take over." << std::endl;
			players_[playerIndex]->setHuman(false); //player is no longer human
			players_[playerIndex] = new ComputerPlayer(*players_[playerIndex]);
			robotTurn(playerIndex); //computer turn is executed;
			turnComplete = true;
		}
	}
}

void Straights::robotTurn(int playerIndex) {
	if(players_[playerIndex]->legalPlays().size() > 0) {
		players_[playerIndex]->cplay(table_);
	} else {
		players_[playerIndex]->cdiscard();
	}
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
	straightsGame->playGame();
}
