#include "Player.h"
#include <iostream>
#include <cassert>

Player::Player(){
	roundScore_ = 0;
	totalScore_ = 0;
	playerIndex_ = 0;
}

Player::Player(char input, int index) {
	isHuman_ = (input == 'h' || input == 'H') ? true : false;
	roundScore_ = 0;
	totalScore_ = 0;
	playerIndex_ = index;
}

Player::~Player(){
	cards_.clear();
	discards_.clear();
	legalPlaysInHand_.clear();
}

int Player::roundScore() const{
	return roundScore_;
}

int Player::totalScore() const {
	return totalScore_;
}

int Player::playerIndex() const {
	return playerIndex_;
}

void Player::addToRoundScore(int addition) {
	roundScore_ += addition;
}

void Player::resetRoundScore() {
	roundScore_ = 0;
}

void Player::addToTotalScore(int addition) {
	totalScore_ +=addition;
}

std::vector<Card> Player::currentHand() const {
	return cards_;
}

std::vector<Card> Player::discards() const {
	return discards_;
}

void Player::clearDiscards() {
	discards_.clear();
}

void Player::addCardToHand(Card card) {
	cards_.push_back(card);
}

void Player::addCardToDiscards(Card card) {
	discards_.push_back(card);
}


void Player::removeCardFromHand(Card card) {
	int index = 0;
	for(std::vector<Card>::iterator it = cards_.begin(); it != cards_.end(); ++it) {
		if(*it == card) {
			break;
		} else {
			index ++;
		}
	}
	cards_.erase(cards_.begin() + index);
}

void Player::setHuman(bool isHuman) {
	isHuman_ = isHuman;
}

bool Player::isHuman() const{
	return isHuman_;
}

void Player::playCard(Card card, Table &table){
	removeCardFromHand(card);

	Suit suit = card.getSuit();
	if(suit == CLUB) {
		table.addClubs(card);
	} else if(suit == DIAMOND) {
		table.addDiamonds(card);
	} else if(suit == HEART) {
		table.addHearts(card);
	} else if(suit == SPADE) {
		table.addSpades(card);
	}

	std::cout << "Player " << playerIndex_ + 1 << " plays " << card << "." << std::endl;
}


void Player::discardCard(Card card) {
	removeCardFromHand(card);
	addCardToDiscards(card);

	int rankInt = card.getRank() + 1;
	addToRoundScore(rankInt);

	std::cout << "Player " << playerIndex_ + 1<< " discards " << card << "." <<std::endl;
}

// bool Player::play(Table& table, Card card){
// 	std::cout<<"BASE\n";
// 	bool validCard = false;
// 	for(std::vector<Card>::iterator it = legalPlaysInHand_.begin(); it != legalPlaysInHand_.end(); ++it) {
// 		if(*it == card) {
// 			validCard = true;
// 		}
// 	}
// 	if(validCard) {
// 		playCard(card, table);
// 		return true;
// 	} else {
// 		std::cout << "This is not a legal play." << std::endl;
// 		return false;
// 	}
// }

// bool Player::discard(Card card){
// 	if(legalPlaysInHand_.size() > 0) {
// 		std::cout << "You have a legal play. You may not discard." << std::endl;
// 		return false;
// 	} else {
// 		bool validCard = false;
// 		for(std::vector<Card>::iterator it = cards_.begin(); it != cards_.end(); ++it) {
// 			if(*it == card) {
// 				validCard = true;
// 			}
// 		}
// 		assert(validCard);

// 		discardCard(card);
// 		return true;
// 	}
// }

void Player::setLegalPlays(Table& table){
	legalPlaysInHand_.clear();
	for(std::vector<Card>::iterator it = cards_.begin(); it != cards_.end(); ++it) {
		if((it->getSuit() == SPADE) && (it->getRank() == SEVEN)) {		
			std::vector<Card> firstMoveHand;
			firstMoveHand.push_back(*it);
			legalPlaysInHand_ = firstMoveHand;
			break;
		}
		if(table.isLegalCard(*it)) {
			legalPlaysInHand_.push_back(*it);
		}
	}
}
std::vector<Card> Player::legalPlays() const{
	return legalPlaysInHand_;
}