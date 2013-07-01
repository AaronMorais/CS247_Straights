#ifndef _COMPUTER_
#define _COMPUTER_

#include "Player.h"
#include "HumanPlayer.h"
#include <vector>

class ComputerPlayer: public Player {
public:
	ComputerPlayer(const Player);
	ComputerPlayer(int index);
	void PlayCard(Table&);
};

#endif