#ifndef _GAME_
#define _GAME_

#include <gtkmm.h>
#include "Straights.h"
#include "MainWindow.h"
#include "Command.h"
#include "Card.h"

class Game {

public:
	Game();
	~Game();
	bool playGame();
	std::vector<Card> getTable();
	std::vector<Card> getCurrentHand();
	void newGame(bool humanPlayer[]);
	int currentPlayer();
	bool humanTurn(Type, Card);
	int playerRoundScore(int);
	int playerTotalScore(int);
	int playerDiscards(int);
	int currentPlayer();

private:
	MainWindow *mainWindow_;
	Straights *straights_;
};

#endif