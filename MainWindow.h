#ifndef _MAINWINDW_
#define _MAINWINDOW_

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include "Card.h"
#include "DeckGUI.h"
#include "Straights.h"

class MainWindow: public Gtk::Window {
public:
	MainWindow();
	~MainWindow();
	void button_quit();
	void startGame();
private:
	Gtk::Image *tableCard[4][13];
	Gtk::Button startGameButton;
	Gtk::HBox tableBox[4];
	Gtk::Frame mainFrame;
	Gtk::Table mainTable;

	DeckGUI deck;
	Straights *straightsGame;
};

#endif