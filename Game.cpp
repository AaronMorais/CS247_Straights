#include "Game.h"

Game::Game(){
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

std::vector<Card> Game::getCurrentHand(){
	int currentPlayer = straights_->currentPlayer;
	return straights_->players_[currentPlayer]->currentHand();
}

bool Game::humanTurn(Type type, int index){
	int currentPlayer = straights_->currentPlayer;
	bool turnComplete = false;
	switch(type){
		case(PLAY): {
			std::vector<Card> currentHandVector = straights_->players_[currentPlayer]->currentHand();
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
	return straights_->table_->isLegalCard(card);
}