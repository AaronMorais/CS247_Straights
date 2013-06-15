#include "Card.h"

class Player {
public:
	Player(std::string);
private:
	bool isHuman_;
	Card *cards_ [];
};