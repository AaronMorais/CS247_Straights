#include "HumanPlayer.h"
#include <iostream>
#include <cassert>

//constructor, sets the default values
HumanPlayer::HumanPlayer(int index){
	roundScore_ = 0;
	totalScore_ = 0;
	playerIndex_ = index;
	isHuman_ = true;
}

//takes in a card and the table, and plays the card onto the table
bool HumanPlayer::play(Card card, Table& table){
	bool validCard = false;
	for(std::vector<Card>::iterator it = legalPlaysInHand_.begin(); it != legalPlaysInHand_.end(); ++it) {
		if(*it == card) { //determines if the desired play card is a legal move
			validCard = true;
		}
	}
	if(validCard) {
		playCard(card, table); //if the card is legal, play the card using the function from the base class
		return true;
	} else {
		std::cout << "This is not a legal play." << std::endl;
		return false;
	}
}

//discards a selected card
bool HumanPlayer::discard(Card card){
	if(legalPlaysInHand_.size() > 0) { //cannot discard if there are legal plays in hand
		std::cout << "You have a legal play. You may not discard." << std::endl;
		return false;
	} else {
		bool validCard = false;
		for(std::vector<Card>::iterator it = cards_.begin(); it != cards_.end(); ++it) {
			if(*it == card) {
				validCard = true; //checks if the card is in the hand
			}
		}
		assert(validCard); //card must be in hand

		discardCard(card); //use the base discard function on the selected card
		return true;
	}
}