#ifndef _TABLE_
#define _TABLE_

#include "Card.h"
#include <vector>
#include <ostream>

class Table{ //handles the cards on the table
	friend std::ostream &operator<<(std::ostream &, const Table &);
public:
	~Table();
	void addClubs(Card); //add club cards to the table
	void addDiamonds(Card);
	void addHearts(Card); 
	void addSpades(Card);
	Card* getTable();
	void empty(); //resets the table
	bool isLegalCard(Card card) const; //checks the cards on the table to determine if a card is legal
	
private:
	void printSuit(std::ostream &, std::vector<Card>) const;
	//keeps tracks of cards on the table by suit
	std::vector<Card> clubs_;
	std::vector<Card> diamonds_;
	std::vector<Card> hearts_;
	std::vector<Card> spades_;
};

std::ostream &operator<<(std::ostream &, const Table &);

#endif