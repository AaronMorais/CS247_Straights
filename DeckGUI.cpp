#include "DeckGUI.h"
#include <algorithm>
#include <iterator>
#include <string>
using std::string;
using std::transform;

// Sets up an array of the Portable Network Graphics (PNG) file names that contain the necessary card images.
// The deck will load the contents into pixel buffers for later use.
const char * image_names[] = {   
	"card_images/0_0.png", "card_images/0_1.png", "card_images/0_2.png", "card_images/0_3.png",
	"card_images/0_4.png", "card_images/0_5.png", "card_images/0_6.png", "card_images/0_7.png",
	"card_images/0_8.png", "card_images/0_9.png", "card_images/0_j.png", "card_images/0_q.png",
	"card_images/0_k.png", 

	"card_images/1_0.png", "card_images/1_1.png", "card_images/1_2.png", "card_images/1_3.png",
	"card_images/1_4.png", "card_images/1_5.png", "card_images/1_6.png", "card_images/1_7.png",
	"card_images/1_8.png", "card_images/1_9.png", "card_images/1_j.png", "card_images/1_q.png",
	"card_images/1_k.png", 

	"card_images/2_0.png", "card_images/2_1.png", "card_images/2_2.png", "card_images/2_3.png",
	"card_images/2_4.png", "card_images/2_5.png", "card_images/2_6.png", "card_images/2_7.png",
	"card_images/2_8.png", "card_images/2_9.png", "card_images/2_j.png", "card_images/2_q.png",
	"card_images/2_k.png", 

	"card_images/3_0.png", "card_images/3_1.png", "card_images/3_2.png", "card_images/3_3.png",
	"card_images/3_4.png", "card_images/3_5.png", "card_images/3_6.png", "card_images/3_7.png",
	"card_images/3_8.png", "card_images/3_9.png", "card_images/3_j.png", "card_images/3_q.png",
	"card_images/3_k.png",
	"card_images/nothing.png"
}; 

const char * legal_image_names[] = {   
	"legal_card_images/0_0.png", "legal_card_images/0_1.png", "legal_card_images/0_2.png", "legal_card_images/0_3.png",
	"legal_card_images/0_4.png", "legal_card_images/0_5.png", "legal_card_images/0_6.png", "legal_card_images/0_7.png",
	"legal_card_images/0_8.png", "legal_card_images/0_9.png", "legal_card_images/0_j.png", "legal_card_images/0_q.png",
	"legal_card_images/0_k.png", 

	"legal_card_images/1_0.png", "legal_card_images/1_1.png", "legal_card_images/1_2.png", "legal_card_images/1_3.png",
	"legal_card_images/1_4.png", "legal_card_images/1_5.png", "legal_card_images/1_6.png", "legal_card_images/1_7.png",
	"legal_card_images/1_8.png", "legal_card_images/1_9.png", "legal_card_images/1_j.png", "legal_card_images/1_q.png",
	"legal_card_images/1_k.png", 

	"legal_card_images/2_0.png", "legal_card_images/2_1.png", "legal_card_images/2_2.png", "legal_card_images/2_3.png",
	"legal_card_images/2_4.png", "legal_card_images/2_5.png", "legal_card_images/2_6.png", "legal_card_images/2_7.png",
	"legal_card_images/2_8.png", "legal_card_images/2_9.png", "legal_card_images/2_j.png", "legal_card_images/2_q.png",
	"legal_card_images/2_k.png", 

	"legal_card_images/3_0.png", "legal_card_images/3_1.png", "legal_card_images/3_2.png", "legal_card_images/3_3.png",
	"legal_card_images/3_4.png", "legal_card_images/3_5.png", "legal_card_images/3_6.png", "legal_card_images/3_7.png",
	"legal_card_images/3_8.png", "legal_card_images/3_9.png", "legal_card_images/3_j.png", "legal_card_images/3_q.png",
	"legal_card_images/3_k.png",
	"legal_card_images/nothing.png"
}; 

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file( name );
} // createPixbuf

DeckGUI::DeckGUI()  {
	// Images can only be loaded once the main window has been initialized, so cannot be done as a static
	// constant array. Instead, use the STL transform algorithm to apply the method createPixbuf to every
	// element in the array of image names, starting with first and ending with the last. New elements are
	// added to the back of deck.
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
			   std::back_inserter(deck), &createPixbuf );	
	transform( &legal_image_names[0], &legal_image_names[G_N_ELEMENTS(legal_image_names)], 
			   std::back_inserter(legalDeck), &createPixbuf );
} // DeckGUI::DeckGUI

DeckGUI::~DeckGUI() {
} // DeckGUI::~DeckGUI

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getCardImage(Card card) {
	int index = ((int) card.getSuit())*13 + ((int) card.getRank());
	return deck[ index ];
} // DeckGUI::getCardImage 

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getNullCardImage() {
	int size = deck.size();
	return deck[ size-1 ];
} // DeckGUI::getNullCardImage


// Returns the legal image to use the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getLegalCardImage(Card card) {
	int index = ((int) card.getSuit())*13 + ((int) card.getRank());
	return legalDeck[ index ];
} // DeckGUI::getCardImage 
