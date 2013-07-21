#include <gtkmm.h>
#include "Straights.h"
#include "MainWindow.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
	Gtk::Main   kit( argc, argv );          
	MainWindow window;
	Gtk::Main::run( window );

 	return 0;
}