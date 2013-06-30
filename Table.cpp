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

void Table::printSuit(std::ostream &out, std::vector<Card> vector) const{
	int size = vector.size();
	std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	for(int j=0; j < RANK_COUNT; j++) {
		bool rankFound = false;
		for(std::vector<Card>::size_type i = 0; i != size; i++) {
			if(vector[i].getRank() == j) {
				rankFound = true;
				break;
			}
		}
		if(rankFound) {
		    out << " ";
		    out << ranks[j];
		}
	}
	if(size == 0) {
		out << " ";
	}
	out << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Table &table){
	out << "Cards on the table: " << std::endl;

	out << "Clubs:";
	table.printSuit(out, table.clubs_);

	out << "Diamonds:";
	table.printSuit(out, table.diamonds_);

	out << "Hearts:";
	table.printSuit(out, table.hearts_);

	out << "Spades:";
	table.printSuit(out, table.spades_);

	return out;
}