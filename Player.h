#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include <vector>

class Player {
public:
	Player(char, int);
	int totalScore() const;
	int roundScore() const;
	int playerIndex() const;
	
	void discardCard(Card);

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

	bool humanDiscard(Card);
	void setLegalPlaysInHand(std::vector<Card>);
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