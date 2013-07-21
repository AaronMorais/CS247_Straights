#include <gtkmm.h>
#include "Straights.h"
#include "MainWindow.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
	int seed = 0;
	if(argc > 1) {
		seed = atoi(argv[1]);
	}  
    srand48(seed);

	Gtk::Main   kit( argc, argv );          
	MainWindow window;
	Gtk::Main::run( window );

 	return 0;
}