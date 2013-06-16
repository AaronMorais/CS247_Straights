#include "Card.h"
#include <vector>

class Player {
public:
	Player(std::string);
	int currentScore() const;
	bool isHuman() const;
	void setHuman(bool isHuman);
	void addToScore(int);
	std::vector<Card> currentHand();
	void addCardToHand(Card);
	void removeCardFromHand(Card *);
	void updateHand(std::vector<Card>);
private:
	bool isHuman_;
	int score_;
	std::vector<Card> cards_;
};