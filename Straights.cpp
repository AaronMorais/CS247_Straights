#include "Straights.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "limits.h"

//constructor, initialized the players, generates deck, and deals the cards to the players
// Straights::Straights() {
// 	invitePlayers(); //collects all the human and computer players
// 	generateDeck(); //generates a deck
// 	createInitialHands();
// }

Straights::Straights(bool humanPlayer[]) {
	for(int i=0; i<NUMBER_OF_PLAYERS; i++) {
		if(humanPlayer[i]) {
			players_[i] = new HumanPlayer(i);
		} else {
			players_[i] = new ComputerPlayer(i);
		}
	}

	gameOver = false;
	cardsRemaining = 52; //Assuming hands will be evenly divisible
	nextPlayer = 0;

	generateDeck(); //generates a deck
	createInitialHands();
}

//gets input for human and computer players
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

//generates a deck
void Straights::generateDeck() {
	int cardIndex = 0;
	for(int suitInt=CLUB; suitInt != SUIT_COUNT; suitInt++) { //goes through the 4 suits
		for(int rankInt=ACE; rankInt != RANK_COUNT; rankInt++) { //goes through all ranks
			cards_[cardIndex] = new Card(static_cast<Suit>(suitInt), static_cast<Rank>(rankInt)); //creates the cards based on the suit and ranks
			cardIndex++;
		}
	}
}

//creates intial hand for all players
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

//shuffles the deck
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

//generates the playing order for the players
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

//starts the game
bool Straights::playGame() {
	bool gameOver = false;
	while(!gameOver) {
		std::cout << "A new round begins. It's player " << (gameOrder[0]+1) << "'s turn to play." << std::endl; 
		while(cardsRemaining != 0) {
			int currentPlayerIndex = gameOrder[nextPlayer];
			players_[currentPlayerIndex]->setLegalPlays(table_); //the player determines its legal plays based on the table
			if(players_[currentPlayerIndex]->isHuman()) {
				currentPlayer = currentPlayerIndex;
				nextPlayer++;
				cardsRemaining--; //every player has either played a card or discarded
				if(nextPlayer > (NUMBER_OF_PLAYERS-1)) {
					nextPlayer = 0;
				}
				return false;
			} else {
				players_[currentPlayerIndex]->computerTurn(table_);
			}
			cardsRemaining--; //every player has either played a card or discarded
			nextPlayer++;
			if(nextPlayer > (NUMBER_OF_PLAYERS-1)) {
				nextPlayer = 0;
			}
		}
		int minimumScore = INT_MAX;
		bool gameOver = false;

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
			return true;
		} else { //new round need to create new hands and a new table
			createInitialHands();
			table_.empty();
		}
		cardsRemaining = 52;
		nextPlayer = 0;
		int currentPlayerIndex = gameOrder[nextPlayer];
		currentPlayer = currentPlayerIndex;
	}	
}

//human turn to play
bool Straights::humanTurn(int playerIndex, Type type, Card card) {
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
	std::cout << ">";
	if(type == PLAY) { //human plays a card on the table
		std::cout << card << std::endl;
		turnComplete = players_[playerIndex]->discard(card);
		if(!turnComplete) {
			turnComplete = players_[playerIndex]->play(table_, card);
		}
	} else if(type == DECK) {
		printDeck();
	} else if(type == QUIT) {
		exit(0);
	} else if(type == RAGEQUIT) {
		std::cout << "Player " << playerIndex+1 << " ragequits. A computer will now take over." << std::endl;
		players_[playerIndex]->setHuman(false); //player is no longer human
		Player* replacementPlayer = new ComputerPlayer(*players_[playerIndex]);
		delete players_[playerIndex];
		players_[playerIndex] = replacementPlayer;
		players_[playerIndex]->computerTurn(table_); //computer turn is executed;
		turnComplete = true;
	}
	return turnComplete;
}

//prints the deck
void Straights::printDeck(){
	for(int i=0; i<CARD_COUNT;i++) {
		if((i%DECK_CARDS_PER_LINE) == 0 && i>0) { //new line when the cards per line has been reached
			std::cout << std::endl;
		}
		std::cout << *cards_[i]; //prints out each card
		std::cout << " ";		 //with a space in between
	}
	std::cout << std::endl;
}

//prints the stats for the end of the round
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

//prints out a card vector
void Straights::printCardVector(std::vector<Card> vector) {
	int size = vector.size();
	for(std::vector<Card>::size_type i = 0; i != (unsigned)size; i++) {
		std::cout << " ";
	    std::cout << vector[i];
	}
	std::cout << std::endl;
}
