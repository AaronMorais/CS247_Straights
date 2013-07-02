#include "ComputerPlayer.h"
#include <iostream>
#include <cassert>

ComputerPlayer::ComputerPlayer(const Player& player){
	roundScore_ = player.roundScore();
	totalScore_ = player.totalScore();
	playerIndex_ = player.playerIndex();
	cards_ = player.currentHand();
	discards_ = player.discards();
	legalPlaysInHand_ = player.legalPlays();
	isHuman_ = false;
}

ComputerPlayer::ComputerPlayer(int index){
	roundScore_ = 0;
	totalScore_ = 0;
	playerIndex_ = index;
	isHuman_ = false;
}

void ComputerPlayer::cplay(Table& table){
	playCard(legalPlaysInHand_.at(0), table);
}

void ComputerPlayer::cdiscard(){
	discardCard(cards_.at(0));
}