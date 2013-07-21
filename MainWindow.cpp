#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow() : mainTable(5,2,true){		
	set_border_width(10);



	mainFrame.set_label("Cards on the table");
	mainFrame.set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
	mainFrame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	add(mainFrame);

	mainFrame.add(mainTable);

	mainTable.attach(startGameButton, 0, 1, 0, 1);
	startGameButton.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::startGame) );
	mainTable.attach(updateButton, 1, 2, 0, 1);
	updateButton.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::updateGame) );

	for(int suitInt=CLUB; suitInt != SUIT_COUNT; suitInt++) { //goes through the 4 suits
		tableBox[suitInt].set_homogeneous(true);
		tableBox[suitInt].set_spacing(10);
		mainTable.attach(tableBox[suitInt], 0, 2, suitInt+1, suitInt+2);
		mainTable.set_row_spacing(suitInt, 10);
		for(int rankInt=ACE; rankInt != RANK_COUNT; rankInt++) { //goes through all ranks
			const Glib::RefPtr<Gdk::Pixbuf> cardTempPixbuf = deck.getCardImage(*new Card(static_cast<Suit>(suitInt), static_cast<Rank>(rankInt))); 
			tableCard[suitInt][rankInt] = new Gtk::Image(cardTempPixbuf);
			tableBox[suitInt].add(*tableCard[suitInt][rankInt]);
		}
	}

	show_all();
}

void MainWindow::startGame() {
	straightsGame = new Straights();
	return;
}


void MainWindow::updateGame() {
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	for(int j=0; j<52; j++) {
		int suitInt = j/13;
		int rankInt = j%13;
		tableCard[suitInt][rankInt]->set(nullCardPixbuf);
	}
	std::vector<Card> tableVector = straightsGame->table_.getTable();
	for(std::vector<Card>::iterator it = tableVector.begin(); it != tableVector.end(); ++it) {
		const Glib::RefPtr<Gdk::Pixbuf> cardTempPixbuf = deck.getCardImage(*it); 
		tableCard[it->getSuit()][it->getRank()]->set(cardTempPixbuf);
		std::cout << *it << std::endl;
	}
	return;
}

void MainWindow::button_quit() {
	hide();
	return;
}

MainWindow::~MainWindow() {

}