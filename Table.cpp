#include "Table.h"

void Table::addClubs(Card card){
	clubs_.push_back(card);
}

void Table::addDiamonds(Card card){
	diamonds_.push_back(card);
}

void Table::addHearts(Card card){
	hearts_.push_back(card);
} 

void Table::addSpades(Card card){
	spades_.push_back(card);
}

std::vector<Card> Table::getClubs(){
	return clubs_;
}

std::vector<Card> Table::getDiamonds(){
	return diamonds_;
}

std::vector<Card> Table::getHearts(){
	return hearts_;
}

std::vector<Card> Table::getSpades(){
	return spades_;
}

void Table::empty(){
	clubs_.clear();		
	diamonds_.clear();
	hearts_.clear();		
	spades_.clear();
}