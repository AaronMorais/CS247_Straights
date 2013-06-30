#include "Player.h"
#include <iostream>

Player::Player(char input, int index) {
	isHuman_ = (input == 'h' || input == 'H') ? true : false;
	roundScore_ = 0;
	totalScore_ = 0;
	playerIndex_ = index;
}

int Player::roundScore() const{
	return roundScore_;
}

int Player::totalScore() const {
	return totalScore_;
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

std::vector<Card> Player::currentHand() {
	return cards_;
}

std::vector<Card> Player::discards() {
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

void Player::discardCard(Card card) {
	removeCardFromHand(card);
	addCardToDiscards(card);

	int rankInt = card.getRank() + 1;
	addToRoundScore(rankInt);

	std::cout << "Player " << playerIndex_+1 << " discards " << card << "." <<std::endl;
}