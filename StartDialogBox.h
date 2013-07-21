#ifndef _STARTDIALOGBOX_
#define _STARTDIALOGBOX_

#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <string>
#include <vector>
#include "MainWindow.h"
using std::string;
using std::vector;

class MainWindow;
class StartDialogBox : Gtk::Dialog {
public:
	// Specifies the parent window of the dialog box and the title of the dialog box.
	StartDialogBox( MainWindow & parentWindow, string title);
	virtual ~StartDialogBox();
private:
	Gtk::CheckButton button[4];
	MainWindow * window_;
}; 

#endif