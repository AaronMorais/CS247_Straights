#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include <vector>

class Player {
public:
	Player(char);
	int totalScore() const;
	int roundScore() const;

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
private:
	bool isHuman_;
	int totalScore_;
	int roundScore_;
	std::vector<Card> cards_;
	std::vector<Card> discards_;
};

#endif