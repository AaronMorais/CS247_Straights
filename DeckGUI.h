#ifndef __DECK_GUI_H
#define __DECK_GUI_H
#include <gdkmm/pixbuf.h>
#include <vector>
#include "Card.h"
using std::vector;

class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Card);   // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();                 // Returns the image to use for the placeholder.
	Glib::RefPtr<Gdk::Pixbuf> getLegalCardImage(Card card);
private:
	vector< Glib::RefPtr< Gdk::Pixbuf > > deck;                   // Contains the pixel buffer images.
	vector< Glib::RefPtr< Gdk::Pixbuf > > legalDeck;                   // Contains the pixel buffer images.
}; // DeckGUI
#endif
