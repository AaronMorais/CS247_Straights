#ifndef _PLAYER_
#define _PLAYER_

#include "Table.h"
#include "Card.h"
#include <vector>

class Player {
public:
	Player();
	Player(char, int);
	int totalScore() const;
	int roundScore() const;
	int playerIndex() const;

	void discardCard(Card);
	void playCard(Card, Table&);

	bool isHuman() const;
	void setHuman(bool isHuman);

	void addToRoundScore(int);
	void resetRoundScore();
	void addToTotalScore(int);

	std::vector<Card> currentHand();
	std::vector<Card> discards();
	void addCardToHand(Card);
	void addCardToDiscards(Card);
	void clearDiscards();
	void removeCardFromHand(Card);

	virtual void playCard(Table&){};

	bool humanPlay(Card, Table&);
	bool humanDiscard(Card);
	void setLegalPlays(Table&);
	std::vector<Card> legalPlays();
private:
	std::vector<Card> legalPlaysInHand_;
protected:	
	int playerIndex_;
	bool isHuman_;
	int totalScore_;
	int roundScore_;
	std::vector<Card> cards_;
	std::vector<Card> discards_;
};

#endif