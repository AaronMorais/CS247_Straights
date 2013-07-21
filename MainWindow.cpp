#include "MainWindow.h"
#include <iostream>
#include <sstream>

MainWindow::MainWindow() : mainBox(false, 10) {		
	set_border_width(10);

	add(mainBox);

	mainBox.add(gameButtonBox);

	gameStartButton.set_label("Start New Game");
	gameStartButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::startGame));
	gameButtonBox.add(gameStartButton);

	gameEndButton.set_label("End Current Game");
	gameEndButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::endGame));
	gameButtonBox.add(gameEndButton);

	tableFrame.set_label("Cards on the table");
	mainBox.add(tableFrame);
	tableFrame.add(tableContainerBox);
	tableContainerBox.set_homogeneous(true);
	tableContainerBox.set_spacing(10);

	Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	for(int i=0; i<4; i++) { //goes through the 4 suits
		tableContainerBox.add(tableBox[i]);
		tableBox[i].set_homogeneous(true);
		tableBox[i].set_spacing(10);
		for(int j=0; j<13; j++) { //goes through all ranks
			tableCard[i][j] = new Gtk::Image(nullCardPixbuf);
			tableBox[i].add(*tableCard[i][j]);
		}
	}

	mainBox.add(playerBox);
	for(int i=0; i<4; i++) { //goes through the 4 players
		playerRageButton[i].set_label("Rage!");
		playerPointsLabel[i].set_label("0 points");
		playerDiscardsLabel[i].set_label("0 discards");

		std::ostringstream oss;
		oss << "Player " << (i+1);
		playerFrame[i].set_label(oss.str());

		playerRageButton[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainWindow::rageQuit), i));

		playerBox.add(playerFrame[i]);
		playerFrame[i].add(playerContainer[i]);
		playerContainer[i].add(playerRageButton[i]);
		playerContainer[i].add(playerPointsLabel[i]);
		playerContainer[i].add(playerDiscardsLabel[i]);
	}

	mainBox.add(handFrame);
	handFrame.set_label("Your hand");
	handFrame.add(handBox);
	for(int i=0; i<13; i++) {
		handCard[i] = new Gtk::Image(nullCardPixbuf);
		handButton[i].set_image(*handCard[i]);
		handButton[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainWindow::selectCard), i));
		handBox.add(handButton[i]);
	}

	show_all();
}

void MainWindow::startGame() {
	StartDialogBox dialog(*this, "Which players are human?");
	straightsGame = new Straights(humanPlayer);
	std::cout << "LOGGG" << std::endl;
	bool over = straightsGame->playGame();
	std::cout << "game played" << std::endl;
	updateGame();
	return;
}

void MainWindow::endGame() {
	hide();
	return;
}

void MainWindow::rageQuit(int index) {
	//computer does move, table updates, next human player can play
	std::cout << "Rage at index: " << index << std::endl;
	return;
}

void MainWindow::selectCard(int index) {
	int currentPlayer = straightsGame->currentPlayer;
	//human clicks on card, table updates, next human plaer can play
	Card card = straightsGame->players_[currentPlayer]->currentHand()[index];
	bool turnComplete = straightsGame->humanTurn(currentPlayer, PLAY, card);

	std::cout << "turn: " << turnComplete << std::endl;
	if(turnComplete) {
		std::cout << "turn is complete" << std::endl;
		bool over = straightsGame->playGame();
		std::cout << currentPlayer << std::endl;
		updateGame();
		std::cout << "Updated" << std::endl;
		if(over) {
			std::cout << "OVER" << std::endl;
		}
	}

	std::cout << "Select at index: " << index << std::endl;
	return;
}

//game over observer

void MainWindow::updateGame() {
	Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	for(int j=0; j<52; j++) {
		int suitInt = j/13;
		int rankInt = j%13;
		tableCard[suitInt][rankInt]->set(nullCardPixbuf);
	}
	std::vector<Card> tableVector = straightsGame->table_.getTable();
	for(std::vector<Card>::iterator it = tableVector.begin(); it != tableVector.end(); ++it) {
		Glib::RefPtr<Gdk::Pixbuf> cardTempPixbuf = deck.getCardImage(*it); 
		tableCard[it->getSuit()][it->getRank()]->set(cardTempPixbuf);
		std::cout << *it << std::endl;
	}
	for(int j=0; j<13; j++) {
		handCard[j]->set(nullCardPixbuf);
	}
	int index = 0;
	int currentPlayer = straightsGame->currentPlayer;
	std::cout << "About to update " << currentPlayer << std::endl;
	std::vector<Card> handVector = straightsGame->players_[currentPlayer]->currentHand();
	for(std::vector<Card>::iterator it = handVector.begin(); it != handVector.end(); ++it) {
		Glib::RefPtr<Gdk::Pixbuf> cardTempPixbuf = deck.getCardImage(*it); 
		handCard[index]->set(cardTempPixbuf);
		index++;
		std::cout << index << std::endl;
	}

	return;
}

MainWindow::~MainWindow() {

}