#ifndef _STRAIGHTS_
#define _STRAIGHTS_

#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Player.h"
#include "Table.h"
#include "Command.h"
#include <vector>
#include "subject.h"
#include "MainWindow.h"

const int NUMBER_OF_PLAYERS = 4;
const int CARD_COUNT = 52;
const int DECK_CARDS_PER_LINE = 13;
const int GAME_OVER_SCORE = 80;

class Straights: public Subject {
	friend class Game;
public:
	Straights(bool[], int, MainWindow *);
	bool playGame();
	std::string gameOverMessage();
private:
	std::string gameOverMessage_;
	void invitePlayers();
	void createInitialHands();

	bool humanTurn(int playerIndex, Type type, Card card);
	Player *players_[NUMBER_OF_PLAYERS]; 

	int gameOrder [NUMBER_OF_PLAYERS];
	void generateGameOrder(int);

	Card *cards_ [CARD_COUNT];	
	void generateDeck();
	void shuffleDeck();

	Table table_;

	void printDeck();
	void printCardVector(std::vector<Card>);
	void printRoundEnd(int);

	bool gameOver;
	int cardsRemaining; //Assuming hands will be evenly divisible
	int currentPlayer;
	int nextPlayer;

};

#endif