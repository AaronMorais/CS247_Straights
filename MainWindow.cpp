#include "MainWindow.h"

MainWindow::MainWindow() : mainBox(true, 10) {
	set_border_width(10);

	mainFrame.set_label("Cards on the table");
	mainFrame.set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
	mainFrame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	add(mainFrame);

	mainFrame.add(mainBox);
	
	for(int i=0; i<5; i++) {
		table[i] = new Gtk::Image();
		mainBox.add(*table[i]);
	}

	mainBox.add(button);

	show_all();
}

MainWindow::~MainWindow() {
	
}