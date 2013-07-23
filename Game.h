#ifndef _GAME_
#define _GAME_

#include <gtkmm.h>
#include "Straights.h"
#include "MainWindow.h"
#include "Command.h"
#include "Card.h"

class Straights;

class Game {
public:
	Game();
	~Game();
	bool playGame();
	std::vector<Card> getTable() const;
	std::vector<Card> getCurrentHand() const;
	void newGame(bool humanPlayer[], int);
	int currentPlayer() const;
	bool humanTurn(Type, int) const;
	int playerRoundScore(int) const;
	int playerTotalScore(int) const;
	int playerDiscards(int) const;
	bool isLegalCardInHand(Card) const;
	std::vector<Card> getDiscards() const;
private:
	MainWindow *mainWindow_;
	Straights *straights_;
};

#endif