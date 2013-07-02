#include "Player.h"
#include <iostream>
#include <cassert>

//default constructor
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

//destructor, clears the card vectors
Player::~Player(){
	cards_.clear();
	discards_.clear();
	legalPlaysInHand_.clear();
}

//returns the score for the round for the player
int Player::roundScore() const{
	return roundScore_;
}

//returns the total score of the player
int Player::totalScore() const {
	return totalScore_;
}

//returns the index of the player
int Player::playerIndex() const {
	return playerIndex_;
}

//increases the round score based on the given parameter
void Player::addToRoundScore(int addition) {
	roundScore_ += addition;
}

//resets the round score
void Player::resetRoundScore() {
	roundScore_ = 0;
}

//add to the total score
void Player::addToTotalScore(int addition) {
	totalScore_ +=addition;
}

//returns the current hand
std::vector<Card> Player::currentHand() const {
	return cards_;
}

//returns all cards discarded by the player
std::vector<Card> Player::discards() const {
	return discards_;
}

//empty the list of discards
void Player::clearDiscards() {
	discards_.clear();
}

//add cards to the hand
void Player::addCardToHand(Card card) {
	cards_.push_back(card);
}

//add specific cards to the discard list
void Player::addCardToDiscards(Card card) {
	discards_.push_back(card);
}

//removes a card from the hand
void Player::removeCardFromHand(Card card) {
	int index = 0;
	for(std::vector<Card>::iterator it = cards_.begin(); it != cards_.end(); ++it) {
		if(*it == card) { //finds the card in the hand
			break;
		} else {
			index ++;
		}
	}
	cards_.erase(cards_.begin() + index); //removes the card from the hand
}

//set human status
void Player::setHuman(bool isHuman) {
	isHuman_ = isHuman;
}

//returns human status
bool Player::isHuman() const{
	return isHuman_;
}

//plays card
void Player::playCard(Card card, Table &table){
	removeCardFromHand(card); //card is first removed from the hand

	Suit suit = card.getSuit(); //determines suit of the card to be played and adds it to the proper table vector
	if(suit == CLUB) {
		table.addClubs(card);
	} else if(suit == DIAMOND) {
		table.addDiamonds(card);
	} else if(suit == HEART) {
		table.addHearts(card);
	} else if(suit == SPADE) {
		table.addSpades(card);
	}

	std::cout << "Player " << playerIndex_ + 1 << " plays " << card << "." << std::endl; //proper output for playing card
}

//player discards card
void Player::discardCard(Card card) {
	removeCardFromHand(card); //first remove card from hand
	addCardToDiscards(card); //adds the card to the list of discards

	int rankInt = card.getRank() + 1; //determines the integer equivalent of the card's rank
	addToRoundScore(rankInt); //adds the rank to the round score

	std::cout << "Player " << playerIndex_ + 1<< " discards " << card << "." <<std::endl; //proper output for discards
}

//sets the legal plays for the player given the table
void Player::setLegalPlays(Table& table){
	legalPlaysInHand_.clear(); //first clear the previous list of legal moves
	for(std::vector<Card>::iterator it = cards_.begin(); it != cards_.end(); ++it) {
		if((it->getSuit() == SPADE) && (it->getRank() == SEVEN)) {//if it's the first move this is the only legal move
			std::vector<Card> firstMoveHand;
			firstMoveHand.push_back(*it);
			legalPlaysInHand_ = firstMoveHand;
			break;
		}
		if(table.isLegalCard(*it)) {
			legalPlaysInHand_.push_back(*it); //determines if the cards in hand are legal and adds to the list
		}
	}
}

//returns the list of legal plays
std::vector<Card> Player::legalPlays() const{
	return legalPlaysInHand_;
}