#ifndef _PLAYER_
#define _PLAYER_

#include "Table.h"
#include "Card.h"
#include <vector>

class Player {
	friend class HumanPlayer;
	friend class ComputerPlayer;
public:
	Player();
	Player(char, int);
	~Player();
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

	std::vector<Card> currentHand() const;
	std::vector<Card> discards() const;
	void addCardToHand(Card);
	void addCardToDiscards(Card);
	void clearDiscards();
	void removeCardFromHand(Card);

	virtual bool play(Table&, Card = *new Card());
	virtual bool discard(Card = *new Card());
	virtual void cplay(Table&){};
	virtual void cdiscard(){};

	void setLegalPlays(Table&);
	std::vector<Card> legalPlays() const;
private:
	std::vector<Card> legalPlaysInHand_;	
	int playerIndex_;
	bool isHuman_;
	int totalScore_;
	int roundScore_;
	std::vector<Card> cards_;
	std::vector<Card> discards_;
};

#endif