#include "Player.cpp"
#include <vector>

const int NUMBER_OF_PLAYERS = 4;
const int CARD_COUNT = 52;
const int DECK_CARDS_PER_LINE = 13;
const int GAME_OVER_SCORE = 80;

class Straights {
public:
	Straights();
private:
	void invitePlayers();
	void createInitialHands();

	void playGame();
	void humanTurn(int playerIndex);
	std::string humanInput();
	void robotTurn(int playerIndex);
	void playCard(int, Card);
	void discardCard(int, Card);
	std::vector<Card> getLegalPlays(std::vector<Card>);
	bool isLegalCard(Card card);

	int gameOrder [NUMBER_OF_PLAYERS];
	void generateGameOrder(int);

	Card *cards_ [CARD_COUNT];	 
	void generateDeck();
	void shuffleDeck();

	Player *players_[NUMBER_OF_PLAYERS]; 

	std::vector<Card> tableClubs_;
	std::vector<Card> tableDiamonds_;
	std::vector<Card> tableHearts_;
	std::vector<Card> tableSpades_;
	void printCardVector(std::vector<Card>);
	void printCardVectorRanks(std::vector<Card>);

	void printRoundEnd(int);
};