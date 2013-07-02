#include "ComputerPlayer.h"
#include <iostream>
#include <cassert>

//copy constructor, used to change a human to a computer
ComputerPlayer::ComputerPlayer(const Player& player){
	roundScore_ = player.roundScore();
	totalScore_ = player.totalScore();
	playerIndex_ = player.playerIndex();
	cards_ = player.currentHand();
	discards_ = player.discards();
	legalPlaysInHand_ = player.legalPlays();
	isHuman_ = false;
}

//constructor for Computer player, sets the initial values
ComputerPlayer::ComputerPlayer(int index){
	roundScore_ = 0;
	totalScore_ = 0;
	playerIndex_ = index;
	isHuman_ = false;
}

//The computer's turn, determines whether a play or discard should be done
void ComputerPlayer::computerTurn(Table &table){
	if(legalPlaysInHand_.size() > 0) {
		play(table);
	} else {
		discard();
	}
}

//computer plays the first legally available card in the hand
void ComputerPlayer::play(Table& table){
	playCard(legalPlaysInHand_.at(0), table);
}

//discards the first card
void ComputerPlayer::discard(){
	discardCard(cards_.at(0));
}