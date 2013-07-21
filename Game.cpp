#include "Game.h"

Game::Game(){
	Gtk::Main kit();          
	mainWindow_ = new MainWindow(this));
	Gtk::Main::run( mainWindow_ );
}
Game::~Game(){}

Game::newGame(bool humanPlayer[]){
	straights_ = new Straights(humanPlayer);
}

bool Game::playGame(){
	if(straights_->playGame()){
		mainWindow_->gameOverDialog(straights_->gameOverMessage());
	}
}

std::vector<Card> Game::getTable(){
	return straights_->table_.getTable();
}

std::vector<Card> Game::getCurrentHand(){
	int currentPlayer = straights_->currentPlayer;
	return straights_->players_[currentPlayer]->currentHand();
}

bool Game::humanTurn(Type type, index){
	int currentPlayer = straights_->currentPlayer;
	bool turnComplete = false;
	switch(type){
		case(RAGEQUIT):
			Card *card = new Card(SPADE, NINE);
			turnComplete = straights_->humanTurn(currentPlayer, RAGEQUIT, *card);
			break;
		case(PLAY):
			std::vector<Card> currentHandVector = straights_->players_[currentPlayer]->currentHand();
			if((unsigned)index >= currentHandVector.size()) {
				return false;
			}

			Card card = currentHandVector[index];
			turnComplete = straights_->humanTurn(currentPlayer, PLAY, card);
			break;
	}
	return turnComplete;
}

int playerRoundScore(int index){
	return straights_->players_[index]->roundScore();
}

int playerTotalScore(int index){
	return straights_->players_[index]->totalScore();
}

int playerDiscards(int index){
	return straights_->players_[index]->discards().size();
}

int currentPlayer(){
	return straights_->currentPlayer;
}