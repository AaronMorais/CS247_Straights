#include "HumanPlayer.h"
#include <iostream>
#include <cassert>

HumanPlayer::HumanPlayer(int index){
	roundScore_ = 0;
	totalScore_ = 0;
	playerIndex_ = index;
	isHuman_ = true;
}

bool HumanPlayer::play(Card card, Table& table){
	bool validCard = false;
	for(std::vector<Card>::iterator it = legalPlaysInHand_.begin(); it != legalPlaysInHand_.end(); ++it) {
		if(*it == card) {
			validCard = true;
		}
	}
	if(validCard) {
		playCard(card, table);
		return true;
	} else {
		std::cout << "This is not a legal play." << std::endl;
		return false;
	}
}

bool HumanPlayer::discard(Card card){
	if(legalPlaysInHand_.size() > 0) {
		std::cout << "You have a legal play. You may not discard." << std::endl;
		return false;
	} else {
		bool validCard = false;
		for(std::vector<Card>::iterator it = cards_.begin(); it != cards_.end(); ++it) {
			if(*it == card) {
				validCard = true;
			}
		}
		assert(validCard);

		discardCard(card);
		return true;
	}
}