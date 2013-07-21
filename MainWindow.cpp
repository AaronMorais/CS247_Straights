#include "MainWindow.h"
#include <iostream>
#include <sstream>
#include <string>
#include "limits.h"

MainWindow::MainWindow(Game *game) : mainBox(false, 10) {		
	gameController = game;
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
		playerRoundPointsLabel[i].set_label("0 round points");
		playerTotalPointsLabel[i].set_label("0 total points");
		playerDiscardsLabel[i].set_label("0 discards");

		std::ostringstream oss;
		oss << "Player " << (i+1);
		playerFrame[i].set_label(oss.str());

		playerRageButton[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainWindow::rageQuit), i));
		playerRageButton[i].set_sensitive(false);

		playerBox.add(playerFrame[i]);
		playerFrame[i].add(playerContainer[i]);
		playerContainer[i].add(playerRageButton[i]);
		playerContainer[i].add(playerRoundPointsLabel[i]);
		playerContainer[i].add(playerTotalPointsLabel[i]);
		playerContainer[i].add(playerDiscardsLabel[i]);
	}

	mainBox.add(handFrame);
	handFrame.set_label("Your hand");
	handFrame.add(handBox);
	for(int i=0; i<13; i++) {
		handCard[i] = new Gtk::Image(nullCardPixbuf);
		handButton[i].set_image(*handCard[i]);
		handButton[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&MainWindow::selectCard), i));
		handButton[i].set_sensitive(false);
		handBox.add(handButton[i]);
	}

	show_all();
}

void MainWindow::startGame() {
	StartDialogBox startDialog(*this, "Which players are human?");
	SeedDialogBox seedDialog(*this, "Enter a Random Seed");
	gameController->newGame(humanPlayer);
	playGame();
	return;
}

void MainWindow::endGame() {
	hide();
	return;
}

void MainWindow::rageQuit(int index) {
	//computer does move, table updates, next human player can play
	
	gameController->humanTurn(RAGEQUIT, 0);

	playGame();

	return;
}

void MainWindow::selectCard(int index) {
	bool turnComplete = gameController->humanTurn(PLAY, index);
	if(turnComplete) {
		playGame();
	}

	return;
}

void MainWindow::playGame() {
	gameController->playGame();
	updateGame();
}

void MainWindow::gameOverDialog(std::string gameOverString){
	updateGame();
	gameOverString += "Start a new game?";

	Gtk::MessageDialog dialog(*this, "Game Over!",
	          false /* use_markup */, Gtk::MESSAGE_INFO,
	          Gtk::BUTTONS_OK_CANCEL);
	dialog.set_secondary_text(gameOverString);
	int result = dialog.run();
	switch (result) {
        case Gtk::RESPONSE_OK:
        	startGame();
        	break;
        case Gtk::RESPONSE_CANCEL:
        	endGame();
			break;
	}
}

void MainWindow::updateGame() {
	Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	for(int j=0; j<52; j++) {
		int suitInt = j/13;
		int rankInt = j%13;
		tableCard[suitInt][rankInt]->set(nullCardPixbuf);
	}

	std::vector<Card> tableVector = gameController->getTable();
	for(std::vector<Card>::iterator it = tableVector.begin(); it != tableVector.end(); ++it) {
		Glib::RefPtr<Gdk::Pixbuf> cardTempPixbuf = deck.getCardImage(*it); 
		tableCard[it->getSuit()][it->getRank()]->set(cardTempPixbuf);
	}
	for(int j=0; j<13; j++) {
		handCard[j]->set(nullCardPixbuf);
		handButton[j].set_sensitive(false);
	}

	int index = 0;

	std::vector<Card> handVector = gameController->getCurrentHand();
	for(std::vector<Card>::iterator it = handVector.begin(); it != handVector.end(); ++it) {
		Glib::RefPtr<Gdk::Pixbuf> cardTempPixbuf = deck.getCardImage(*it); 
		handCard[index]->set(cardTempPixbuf);
		handButton[index].set_sensitive(true);
		index++;
	}

	int currentPlayer = gameController->currentPlayer();

	for(int i=0; i<4; i++) { //goes through the 4 players
		std::ostringstream oss;

		int roundScore = gameController->playerRoundScore(i);
		oss << roundScore << " round point";
		if(roundScore != 1) {
			oss << "s";
		}
		playerRoundPointsLabel[i].set_label(oss.str());

		oss.str(std::string());

		int totalScore = gameController->playerTotalScore(i) + gameController->playerRoundScore(i);
		oss << totalScore << " total point";
		if(totalScore != 1) {
			oss << "s";
		}
		playerTotalPointsLabel[i].set_label(oss.str());

		oss.str(std::string());
		int discards = gameController->playerDiscards(i);
		oss << discards << " discard";
		if(discards != 1) {
			oss << "s";
		}

		playerDiscardsLabel[i].set_label(oss.str());

		if(currentPlayer == i) {
			playerRageButton[i].set_sensitive(true);
		} else {
			playerRageButton[i].set_sensitive(false);
		}
	}

	std::ostringstream oss;
	oss << "Player " << (currentPlayer+1) << "'s hand";
	handFrame.set_label(oss.str());

	return;
}

MainWindow::~MainWindow() {

}