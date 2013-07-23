#ifndef _MAINWINDOW_
#define _MAINWINDOW_

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/eventbox.h>
#include <string>
#include "Card.h"
#include "DeckGUI.h"
#include "StartDialogBox.h"
#include "SeedDialogBox.h"
#include "Game.h"
#include "subject.h"
#include "Straights.h"

const int CARDS_PER_HAND = 13;

class Game;
class MainWindow: public Gtk::Window, public Observer {
friend class StartDialogBox;
friend class SeedDialogBox;
friend class Game;
public:
	MainWindow(Game*);
	~MainWindow();
	virtual void update();	// Observer Pattern: concrete update() method
private:
	Game *gameController;
	Gtk::VBox mainBox;

	Gtk::HBox gameButtonBox;
	Gtk::Button gameStartButton;
	Gtk::Button gameEndButton;
	Gtk::Button gameSeedButton;

	Gtk::Frame tableFrame;
	Gtk::VBox tableContainerBox;
	Gtk::HBox tableBox[NUMBER_OF_PLAYERS];
	Gtk::Image *tableCard[NUMBER_OF_PLAYERS][CARDS_PER_HAND];
	
	Gtk::HBox playerBox;
	Gtk::Frame playerFrame[NUMBER_OF_PLAYERS];
	Gtk::VBox playerContainer[NUMBER_OF_PLAYERS];
	Gtk::Button playerRageButton[NUMBER_OF_PLAYERS];
	Gtk::Label playerRoundPointsLabel[NUMBER_OF_PLAYERS];
	Gtk::Label playerTotalPointsLabel[NUMBER_OF_PLAYERS];
	Gtk::Label playerDiscardsLabel[NUMBER_OF_PLAYERS];

	Gtk::Frame handFrame;
	Gtk::HBox handBox;
	Gtk::Button handButton[CARDS_PER_HAND];
	Gtk::Image *handCard[CARDS_PER_HAND];

	Gtk::Frame discardsFrame;
	Gtk::Label discardsLabel;

	DeckGUI deck;
	Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf;

	bool humanPlayer[NUMBER_OF_PLAYERS];
	int seed;

	void startGame();
	void endGame();
	void seedGame();
	void rageQuit(int);
	void selectCard(int);
	void updateGame();
	void playGame();
	void gameOverDialog(std::string);
	void changeSeed();
    void updateTable();
    void updateHand();
    void updatePlayerInfo();
    void updateDiscards();
};

#endif