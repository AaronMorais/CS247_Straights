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


	bool isHuman() const;
	void setHuman(bool isHuman);

	void addToRoundScore(int);
	void resetRoundScore();
	void addToTotalScore(int);

	std::vector<Card> currentHand() const;
	std::vector<Card> discards() const;
	void addCardToHand(Card);
	void clearDiscards();

	virtual bool play(Table&, Card){};
	virtual bool discard(Card){};
	virtual void computerTurn(Table&){};
	void setLegalPlays(Table&);
	std::vector<Card> legalPlays() const;

private:
	void removeCardFromHand(Card);
	void addCardToDiscards(Card);
	void discardCard(Card);
	void playCard(Card, Table&);
	std::vector<Card> legalPlaysInHand_;	
	int playerIndex_;
	bool isHuman_;
	int totalScore_;
	int roundScore_;
	std::vector<Card> cards_;
	std::vector<Card> discards_;
};

#endif