#include "Game.h"

Game::Game(){
    srand48(0);
	mainWindow_ = new MainWindow(this);
	Gtk::Main::run(*mainWindow_);
}
Game::~Game(){}

void Game::newGame(bool humanPlayer[]){
	straights_ = new Straights(humanPlayer);
}

bool Game::playGame(){
	if(straights_->playGame()){
		mainWindow_->gameOverDialog(straights_->gameOverMessage());
		return true;
	}
	return false;
}

std::vector<Card> Game::getTable(){
	return straights_->table_.getTable();
}

bool cardComparison(const Card &a, const Card &b) {
	return ((a.getSuit() < b.getSuit()) ||
		(a.getSuit() == b.getSuit()) && (a.getRank() < b.getRank()));
}

std::vector<Card> Game::getCurrentHand(){
	int currentPlayer = straights_->currentPlayer;
	std::vector<Card> currentHandVector = straights_->players_[currentPlayer]->currentHand();
	std::sort (currentHandVector.begin(), currentHandVector.end(), &cardComparison);
	return currentHandVector;
}

bool Game::humanTurn(Type type, int index){
	int currentPlayer = straights_->currentPlayer;
	bool turnComplete = false;
	switch(type){
		case(PLAY): {
			std::vector<Card> currentHandVector = getCurrentHand();
			if((unsigned)index >= currentHandVector.size()) {
				return false;
			}

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

int Game::playerRoundScore(int index){
	return straights_->players_[index]->roundScore();
}

int Game::playerTotalScore(int index){
	return straights_->players_[index]->totalScore();
}

int Game::playerDiscards(int index){
	return straights_->players_[index]->discards().size();
}

int Game::currentPlayer(){
	return straights_->currentPlayer;
}

bool Game::isLegalCardInHand(Card card){
	if(straights_->cardsRemaining == CARD_COUNT-1) {
		return (card.getSuit() == SPADE && card.getRank() == SEVEN);
	}
	return straights_->table_.isLegalCard(card);
}

std::vector<Card> Game::getDiscards() {
	std::vector<Card> discardVector;
	for(int i=0; i < NUMBER_OF_PLAYERS; i++) {
		std::vector<Card> playerDiscards = straights_->players_[i]->discards();
		discardVector.insert(discardVector.end(), playerDiscards.begin(), playerDiscards.end());
	}
	std::sort (discardVector.begin(), discardVector.end(), &cardComparison);
	return discardVector;
}
