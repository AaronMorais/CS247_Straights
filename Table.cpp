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

void Table::empty(){ //clears all card vectors
	clubs_.clear();		
	diamonds_.clear();
	hearts_.clear();		
	spades_.clear();
}

bool Table::isLegalCard(Card card) const{
	Suit suit = card.getSuit(); //gets detail of card
	Rank rank = card.getRank();
	if(rank == SEVEN) { //7 of any suit is always a legal move
		return true;
	}
	int rankInt = rank; 
	int left = rankInt - 1; //cards of adjacent rank are legal
	int right = rankInt + 1;

	std::vector<Card> suitVector; //get all cards on the table with the legal suit
	if(suit == CLUB) {
		suitVector = clubs_;
	} else if(suit == DIAMOND) {
		suitVector = diamonds_;
	} else if(suit == HEART) {
		suitVector = hearts_;
	} else if(suit == SPADE) {
		suitVector = spades_;
	}

	//iterate through all previously played cards with the same suit and determine if it is of adjacent rank
	for(std::vector<Card>::iterator it = suitVector.begin(); it != suitVector.end(); ++it) {
		Rank cardRank = it->getRank();
		int cardRankInt = cardRank;
		if(cardRank == left || cardRank == right) {
			return true; //card is legal
		}
	}
	return false; //no match, card is not legal
}

void Table::printSuit(std::ostream &out, std::vector<Card> vector) const{//helper function for << operator
	int size = vector.size(); //number of cards of the suit that will be printed
	std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	if(size == 0) { //no cards of this suit
		out << " ";
	} else {
		for(int j=0; j < RANK_COUNT; j++) {//in order to print the cards in order
			bool rankFound = false;
			for(std::vector<Card>::size_type i = 0; i != size; i++) {
				if(vector[i].getRank() == j) {//a card matching the rank was found
					rankFound = true;
					break;
				}
			}
			if(rankFound) {
			    out << " ";
			    out << ranks[j];
			}
		}
	}
	out << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Table &table){
	out << "Cards on the table: " << std::endl;

	out << "Clubs:"; //cards on the table are printed by suit in this order
	table.printSuit(out, table.clubs_);

	out << "Diamonds:";
	table.printSuit(out, table.diamonds_);

	out << "Hearts:";
	table.printSuit(out, table.hearts_);

	out << "Spades:";
	table.printSuit(out, table.spades_);

	return out;
}