#include "Game.h"

Game::Game(){
    srand48(0);
	mainWindow_ = new MainWindow(this);
	Gtk::Main::run(*mainWindow_);
}
Game::~Game(){}

//instantiates a new straights game, feeding in the human players and the seed to use
void Game::newGame(bool humanPlayer[], int seed){
	straights_ = new Straights(humanPlayer, seed, mainWindow_);
}

//calls the play game method in straights
bool Game::playGame(){
	if(straights_->playGame()){ //if the response from straights is true, then the game is over
		mainWindow_->gameOverDialog(straights_->gameOverMessage());
		return true;
	}
	return false;
}

//gets the cards on the table from straights
std::vector<Card> Game::getTable(){
	return straights_->table_.getTable();
}

//compares two cards and returns the "lower" card
bool cardComparison(const Card &a, const Card &b) {
	return ((a.getSuit() < b.getSuit()) ||
		((a.getSuit() == b.getSuit()) && (a.getRank() < b.getRank())));
}

//goes into straights to get the hand of the current player, returning a sorted hand
std::vector<Card> Game::getCurrentHand(){
	int currentPlayer = straights_->currentPlayer;
	std::vector<Card> currentHandVector = straights_->players_[currentPlayer]->currentHand();
	std::sort (currentHandVector.begin(), currentHandVector.end(), &cardComparison);
	return currentHandVector;
}

//runs a human turn in the straights class based on the type of command
bool Game::humanTurn(Type type, int index){
	int currentPlayer = straights_->currentPlayer;
	bool turnComplete = false;
	switch(type){
		case(PLAY): { //index is used here to determine which card is selected
			std::vector<Card> currentHandVector = getCurrentHand();

			Card card = currentHandVector[index];
			turnComplete = straights_->humanTurn(currentPlayer, PLAY, card);
			break;
		}
		case(RAGEQUIT): {
			Card *emptyCard = new Card(SPADE, NINE);
			turnComplete = straights_->humanTurn(currentPlayer, RAGEQUIT, *emptyCard);
			break;
		}
		default:
			break;
	}
	return turnComplete;
}

//gets the player's score for the round
int Game::playerRoundScore(int index){
	return straights_->players_[index]->roundScore();
}

//gets the player's total score
int Game::playerTotalScore(int index){
	return straights_->players_[index]->totalScore();
}

//returns the number of discards the player has
int Game::playerDiscards(int index){
	return straights_->players_[index]->discards().size();
}

//gets the current player from straights
int Game::currentPlayer(){
	return straights_->currentPlayer;
}

//uses the straights' table to determine if a card is legal
bool Game::isLegalCardInHand(Card card){
	if(straights_->cardsRemaining == CARD_COUNT-1) {
		return (card.getSuit() == SPADE && card.getRank() == SEVEN);
	}
	return straights_->table_.isLegalCard(card);
}

//gets the list of all discards from straights
std::vector<Card> Game::getDiscards() {
	std::vector<Card> discardVector;
	for(int i=0; i < NUMBER_OF_PLAYERS; i++) {
		std::vector<Card> playerDiscards = straights_->players_[i]->discards();
		discardVector.insert(discardVector.end(), playerDiscards.begin(), playerDiscards.end());
	}
	std::sort (discardVector.begin(), discardVector.end(), &cardComparison);
	return discardVector;
}
