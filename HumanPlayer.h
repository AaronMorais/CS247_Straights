#ifndef _HUMAN_
#define _HUMAN_

#include "Player.h"
#include <vector>

class HumanPlayer: public Player {
public:
	HumanPlayer(int index);
	bool play(Table&, Card);
	bool discard(Card);
};

#endif