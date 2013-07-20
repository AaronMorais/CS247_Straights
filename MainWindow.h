#ifndef _MAINWINDW_
#define _MAINWINDOW_

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>

class MainWindow: public Gtk::Window {
public:
	MainWindow();
	~MainWindow();
private:
	Gtk::Image *table[5];
	Gtk::Button button;
	Gtk::HBox mainBox;
	Gtk::Frame mainFrame;
};

#endif