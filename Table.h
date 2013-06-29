#ifndef _TABLE_
#define _TABLE_

#include "Card.h"
#include <vector>

class Table{
public:
	void addClubs(Card);
	void addDiamonds(Card);
	void addHearts(Card); 
	void addSpades(Card);
	std::vector<Card> getClubs();
	std::vector<Card> getDiamonds();
	std::vector<Card> getHearts();
	std::vector<Card> getSpades();
	void empty();
	
private:
	std::vector<Card> clubs_;
	std::vector<Card> diamonds_;
	std::vector<Card> hearts_;
	std::vector<Card> spades_;
};

#endif