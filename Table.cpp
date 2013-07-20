#include "Table.h"

//destructor, clears the card vectors
Table::~Table(){
	clubs_.clear();
	diamonds_.clear();
	hearts_.clear();
	spades_.clear();
}

//add clubs to the club vector
void Table::addClubs(Card card){
	clubs_.push_back(card);
	numberOfCardsOnTable++;
}

//add a diamond card to the diamonds vector
void Table::addDiamonds(Card card){
	diamonds_.push_back(card);
	numberOfCardsOnTable++;
}

//add a heart card to the cards vector
void Table::addHearts(Card card){
	hearts_.push_back(card);
	numberOfCardsOnTable++;
} 

//add spades card to the cards vector
void Table::addSpades(Card card){
	spades_.push_back(card);
	numberOfCardsOnTable++;
}

*Card Table::getTable(){
	Card onTable[numberOfCardsOnTable];
	int j=0;
	for(int i = 0; i < 4; i++){
		std::vector<Card> suitVector; 
		switch(i){
			case 1:
				suitVector = clubs_;
			case 2:
				suitVector = diamonds_;
			case 3:
				suitVector = hearts_;
			case 4:
				suitVector = spades_;
		}
		for(std::vector<Card>::iterator it = suitVector.begin(); it != suitVector.end(); ++it) {
			onTable[j++] = &*it;
		}
	}
	return *onTable;
}

void Table::empty(){ //clears all card vectors
	clubs_.clear();		
	diamonds_.clear();
	hearts_.clear();		
	spades_.clear();
	numberOfCardsOnTable = 0;
}

//determines if a card is legal based on the current cards on the table
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
		if(cardRank == left || cardRank == right) {
			return true; //card is legal
		}
	}
	return false; //no match, card is not legal
}

//helper function for << operator
void Table::printSuit(std::ostream &out, std::vector<Card> vector) const{
	int size = vector.size(); //number of cards of the suit that will be printed
	std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
	if(size == 0) { //no cards of this suit
		out << " ";
	} else {
		for(int j=0; j < RANK_COUNT; j++) {//in order to print the cards in order
			bool rankFound = false;
			for(std::vector<Card>::size_type i = 0; i != (unsigned)size; i++) {
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

//ostream to print out the cards on the table by suit
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