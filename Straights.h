#ifndef _STRAIGHTS_
#define _STRAIGHTS_

#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Player.h"
#include "Table.h"
#include "Command.h"
#include <vector>

const int NUMBER_OF_PLAYERS = 4;
const int CARD_COUNT = 52;
const int DECK_CARDS_PER_LINE = 13;
const int GAME_OVER_SCORE = 80;

class Straights {
	friend class MainWindow;
public:
	Straights();
	void playGame();
private:
	void invitePlayers();
	void createInitialHands();

	void humanTurn(int playerIndex);
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
};

#endif