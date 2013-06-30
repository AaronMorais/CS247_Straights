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

void Table::empty(){
	clubs_.clear();		
	diamonds_.clear();
	hearts_.clear();		
	spades_.clear();
}

bool Table::isLegalCard(Card card) const{
	Suit suit = card.getSuit();
	Rank rank = card.getRank();
	if(rank == SEVEN) {
		return true;
	}
	int rankInt = rank;
	//TODO - find out why using -- and ++ was behaving incorrectly
	int left = rankInt - 1;
	int right = rankInt + 1;

	std::vector<Card> suitVector;
	if(suit == CLUB) {
		suitVector = clubs_;
	} else if(suit == DIAMOND) {
		suitVector = diamonds_;
	} else if(suit == HEART) {
		suitVector = hearts_;
	} else if(suit == SPADE) {
		suitVector = spades_;
	}
	for(std::vector<Card>::iterator it = suitVector.begin(); it != suitVector.end(); ++it) {
		Rank cardRank = it->getRank();
		int cardRankInt = cardRank;
		if(cardRank == left || cardRank == right) {
			return true;
		}
	}
	return false;
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