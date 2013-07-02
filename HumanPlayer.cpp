#include "HumanPlayer.h"
#include <iostream>
#include <cassert>

HumanPlayer::HumanPlayer(int index){
	playerIndex_ = 0;
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