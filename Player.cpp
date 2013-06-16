#include "Player.h"
#include <iostream>

Player::Player(std::string input) {
	isHuman_ = (input == "h" || input == "H") ? true : false;
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

void Player::addCardToHand(Card card) {
	cards_.push_back(card);
}

void Player::addCardToDiscards(Card card) {
	discards_.push_back(card);
}


void Player::removeCardFromHand(Card *card) {
	int index = 0;
	for(std::vector<Card>::iterator it = cards_.begin(); it != cards_.end(); ++it) {
		if(&it && &card) {
			break;
		} else {
			index ++;
		}
	}
	std::cout << "Erasing :" << &card << std::endl;
	cards_.erase(cards_.begin() + index);
}

void Player::updateHand(std::vector<Card> cards) {
	cards_ = cards;
}

void Player::setHuman(bool isHuman) {
	isHuman_ = isHuman;
}

bool Player::isHuman() const{
	return isHuman_;
}