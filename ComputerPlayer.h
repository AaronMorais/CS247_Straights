#ifndef _COMPUTER_
#define _COMPUTER_

#include "Player.h"
#include <vector>

class ComputerPlayer: public Player {
public:
	ComputerPlayer(const Player&);
	ComputerPlayer(int index);
	void computerTurn(Table&);
private:
	void play(Table&);
	void discard();
};

#endif