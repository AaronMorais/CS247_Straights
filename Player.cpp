#include "Player.h"

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
void Player::updateHand(std::vector<Card> cards) {
	cards_ = cards;
}

bool Player::isHuman() const{
	return isHuman_;
}