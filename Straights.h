#include "Deck.cpp"
#include "Player.cpp"

const int NUMBER_OF_PLAYERS = 4;

class Straights {
public:
	Straights();
private:
	Deck *deck_;
	Player *players_[NUMBER_OF_PLAYERS]; 
	void invitePlayers();
};