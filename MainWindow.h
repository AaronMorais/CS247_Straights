#ifndef _MAINWINDOW_
#define _MAINWINDOW_

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/messagedialog.h>
#include <string>
#include "Card.h"
#include "DeckGUI.h"
#include "Straights.h"
#include "StartDialogBox.h"
#include "SeedDialogBox.h"
#include "Game.h"

class Game;

class MainWindow: public Gtk::Window {
friend class StartDialogBox;
public:
	MainWindow(Game*);
	~MainWindow();
	void startGame();
	void endGame();
	void rageQuit(int);
	void selectCard(int);
	void updateGame();
	void playGame();
	void gameOverDialog(std::string);
private:
	Game *gameController;
	Gtk::VBox mainBox;

	Gtk::HBox gameButtonBox;
	Gtk::Button gameStartButton;
	Gtk::Button gameEndButton;

	Gtk::Frame tableFrame;
	Gtk::VBox tableContainerBox;
	Gtk::HBox tableBox[4];
	Gtk::Image *tableCard[4][13];
	
	Gtk::HBox playerBox;
	Gtk::Frame playerFrame[4];
	Gtk::VBox playerContainer[4];
	Gtk::Button playerRageButton[4];
	Gtk::Label playerRoundPointsLabel[4];
	Gtk::Label playerTotalPointsLabel[4];
	Gtk::Label playerDiscardsLabel[4];

	Gtk::Frame handFrame;
	Gtk::HBox handBox;
	Gtk::Button handButton[13];
	Gtk::Image *handCard[13];

	DeckGUI deck;
	Straights *straightsGame;
	bool humanPlayer[4];
};

#endif