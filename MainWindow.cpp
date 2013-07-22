#include "MainWindow.h"
#include <iostream>
#include <sstream>
#include <string>
#include "limits.h"

//sets up all the elements on the window
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

	gameSeedButton.set_label("Seed Next Game");
	gameSeedButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::seedGame));
	gameButtonBox.add(gameSeedButton);

	tableFrame.set_label("Cards on the table");
	mainBox.add(tableFrame);
	tableFrame.add(tableContainerBox);
	tableContainerBox.set_homogeneous(true);
	tableContainerBox.set_spacing(10);

	nullCardPixbuf = deck.getNullCardImage();
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

	mainBox.add(discardsFrame);
	discardsFrame.set_label("Discards: ");
	discardsFrame.add(discardsLabel);

	show_all();
}

//when the start game button is clicked
void MainWindow::startGame() {
	//Dialog box for setting human players
	StartDialogBox startDialog(*this, "Which players are human?");
	//Tells the controller to initialize a new game
	gameController->newGame(humanPlayer, seed);
	playGame();
	return;
}

//End game button is clicked, window closes
void MainWindow::endGame() {
	hide();
	return;
}

//Seed game button is clicked
void MainWindow::seedGame() {
	//Dialog box for user to input new seed
	SeedDialogBox seedDialog(*this, "Enter a Random Seed");
	return;
}

void MainWindow::rageQuit(int index) {
	//computer does move, table updates, next human player can play
	
	gameController->humanTurn(RAGEQUIT, 0);
	playGame();

	return;
}

//response for when a card in the hand is clicked
void MainWindow::selectCard(int index) {
	bool turnComplete = gameController->humanTurn(PLAY, index);
	if(turnComplete) {
		playGame();
	}

	return;
}

//tells the controller to play the game
void MainWindow::playGame() {
	gameController->playGame();
	updateGame();
}

//dialog for when the game ends
void MainWindow::gameOverDialog(std::string gameOverString){
	updateGame();
	gameOverString += "Start a new game?";

	//new dialog with the title Game Over, has ok and cancel buttons
	Gtk::MessageDialog dialog(*this, "Game Over!",
	          false /* use_markup */, Gtk::MESSAGE_INFO,
	          Gtk::BUTTONS_OK_CANCEL);
	dialog.set_secondary_text(gameOverString); //text is set based on the passed in string
	int result = dialog.run(); //dialog runs
	switch (result) {
        case Gtk::RESPONSE_OK: //if ok, play a new game
        	startGame();
        	break;
        case Gtk::RESPONSE_CANCEL: //if cancel, the user doesn't wish to continue playing so close the window
        	endGame();
			break;
	}
}

//updates various elements on the window
void MainWindow::updateGame() {
    updateTable();
    updateHand();
    updatePlayerInfo();
    updateDiscards();
    return;
}

//The table is the cards that have been played
void MainWindow::updateTable() {
	//starts will all 52 cards set as null cards
	for(int j=0; j<52; j++) {
		int suitInt = j/13;
		int rankInt = j%13;
		tableCard[suitInt][rankInt]->set(nullCardPixbuf);
	}

	//gets information about the table  through the game controller and updates accordingly
	std::vector<Card> tableVector = gameController->getTable();
	for(std::vector<Card>::iterator it = tableVector.begin(); it != tableVector.end(); ++it) {
		Glib::RefPtr<Gdk::Pixbuf> cardTempPixbuf = deck.getCardImage(*it); 
		tableCard[it->getSuit()][it->getRank()]->set(cardTempPixbuf);
	}
    return;
}

//updates the display for the cards in the player's hand
void MainWindow::updateHand() {
	//starts with all 13 cards in the hand as null unclickable cards
	for(int j=0; j<13; j++) {
		handCard[j]->set(nullCardPixbuf);
		handButton[j].set_sensitive(false);
	}

	int index = 0;

	//gets information on what to display via the game controller
	std::vector<Card> handVector = gameController->getCurrentHand();
	for(std::vector<Card>::iterator it = handVector.begin(); it != handVector.end(); ++it) {
		Glib::RefPtr<Gdk::Pixbuf> cardTempPixbuf;
		if(gameController->isLegalCardInHand(*it)){ //if the card is legal then take the legal card image
			cardTempPixbuf = deck.getLegalCardImage(*it); 
		} else { //otherwise take the standard card image
			cardTempPixbuf = deck.getCardImage(*it); 
		}
		handCard[index]->set(cardTempPixbuf);
		handButton[index].set_sensitive(true); //make the button clickable
		index++;
	}
    
    std::ostringstream oss;
	int currentPlayer = gameController->currentPlayer();
	oss << "Player " << (currentPlayer+1) << "'s hand";
	handFrame.set_label(oss.str());
    return;
}

//updates the four player status blocks
void MainWindow::updatePlayerInfo() {
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
		//only the current player should have an active ragequit button
		if(currentPlayer == i) {
			playerRageButton[i].set_sensitive(true);
		} else {
			playerRageButton[i].set_sensitive(false);
		}
	}
	return;
}

//updates the list of discards at the bottom of the window
void MainWindow::updateDiscards() {
	std::ostringstream oss;
	oss.str(std::string());
	std::vector<Card> discardVector = gameController->getDiscards(); //gets the list of discards from the game controller
	for(std::vector<Card>::iterator it = discardVector.begin(); it != discardVector.end(); ++it) {
		oss << *it << " ";
	}
	discardsLabel.set_label(oss.str());
    return;
}

MainWindow::~MainWindow() {

}