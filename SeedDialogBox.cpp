#include "SeedDialogBox.h"
#include <gtkmm/stock.h>
#include <iostream>

// Specifies the parent window of the dialog box and the title of the dialog box.
SeedDialogBox::SeedDialogBox( MainWindow & parentWindow, string title) : Dialog( title, parentWindow, true, true ) {
	this->set_default_size(300,100);

	window_ = &parentWindow;
	Gtk::VBox* contentArea = this->get_vbox();

	contentArea->add(seedEntry);
	seedEntry.set_text("0");
	
	// Add a standard "ok" buttons with the appropriate responses when clicked.
    Gtk::Button * okButton = add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	contentArea->add(*okButton);

	show_all_children();
	
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
	        std::string seedString = seedEntry.get_text();
			int seed = atoi(seedString.c_str());
		    srand48(seed);
            break;
    } 
} 

SeedDialogBox::~SeedDialogBox() {
} 
