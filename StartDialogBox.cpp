#include "StartDialogBox.h"
#include <gtkmm/stock.h>
#include <iostream>

// Specifies the parent window of the dialog box and the title of the dialog box.
StartDialogBox::StartDialogBox( MainWindow & parentWindow, string title) : Dialog( title, parentWindow, true, true ) {
	this->set_default_size(300,300);

	window_ = &parentWindow;
	Gtk::VBox* contentArea = this->get_vbox();
	
	// Set up checkbuttons, one for each player to indicate human
	for ( int i = 0; i < 4; i++ ) {
		std::ostringstream oss;
		oss << "Player " << (i+1);
		button[i].set_label(oss.str());
		contentArea->add(button[i]);
	} 
	
	// Add a standard "ok" buttons with the appropriate responses when clicked.
    add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	show_all_children();
	
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK: //If ok is clicked
            for (int i = 0; i < 4; i++) {
				window_->humanPlayer[i] = button[i].get_active(); //keep track of which buttons were seleced
			} 
            break;
    } 
} 

StartDialogBox::~StartDialogBox() {
} 
