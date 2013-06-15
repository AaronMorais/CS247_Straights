#include "Player.h"

Player::Player(std::string input) {
	isHuman_ = (input == "h" || input == "H") ? true : false;
}