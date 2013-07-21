#include "Game.h"
#include <gtkmm.h>

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);          
	Game *game = new Game();

 	return 0;
}