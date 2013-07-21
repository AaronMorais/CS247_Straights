#include "StartDialogBox.h"
#include <gtkmm/stock.h>
#include <iostream>

// Specifies the parent window of the dialog box and the title of the dialog box.
StartDialogBox::StartDialogBox( MainWindow & parentWindow, string title) : Dialog( title, parentWindow, true, true ) {
	this->set_default_size(300,300);

	window_ = &parentWindow;
	Gtk::VBox* contentArea = this->get_vbox();
	
	// Set up a group of radio buttons, one per card in human player's hand plus the top card of the kitty.
	for ( int i = 0; i < 4; i++ ) {
		std::ostringstream oss;
		oss << "Player " << (i+1);
		button[i].set_label(oss.str());
		contentArea->add(button[i]);
	} 
	
	// Add a standard "ok" buttons with the appropriate responses when clicked.
    Gtk::Button * okButton = add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	contentArea->add(*okButton);

	show_all_children();
	
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            for (int i = 0; i < 4; i++) {
				window_->humanPlayer[i] = button[i].get_active();
			} 
            break;
    } 
} 

StartDialogBox::~StartDialogBox() {
} 
