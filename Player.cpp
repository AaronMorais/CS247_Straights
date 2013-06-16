#include "Player.h"
#include <iostream>

Player::Player(std::string input) {
	isHuman_ = (input == "h" || input == "H") ? true : false;
}

int Player::currentScore() const{
	return score_;
}

void Player::addToScore(int addition) {
	score_ += addition;
}

std::vector<Card> Player::currentHand() {
	return cards_;
}

void Player::addCardToHand(Card card) {
	cards_.push_back(card);
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