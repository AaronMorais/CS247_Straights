#ifndef _SEEDDIALOGBOX_
#define _SEEDDIALOGBOX_

#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <string>
#include <vector>
#include "MainWindow.h"
using std::string;
using std::vector;

class MainWindow;
class SeedDialogBox : Gtk::Dialog {
public:
	// Specifies the parent window of the dialog box and the title of the dialog box.
	SeedDialogBox( MainWindow & parentWindow, string title);
	virtual ~SeedDialogBox();
private:
	Gtk::Entry seedEntry;
	MainWindow * window_;
}; 

#endif