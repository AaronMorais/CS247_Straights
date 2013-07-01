#include "ComputerPlayer.h"
#include <iostream>
#include <cassert>

ComputerPlayer::ComputerPlayer(const Player& player){
	roundScore_ = player.roundScore();
	totalScore_ = player.totalScore();
	playerIndex_ = player.playerIndex();
}

ComputerPlayer::ComputerPlayer(int index){
	playerIndex_ = index;
}

void ComputerPlayer::PlayCard(Table& table){
	playCard(cards_.at(0), table);
}