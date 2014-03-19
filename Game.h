//Game.h
#include "Player.h"
#include "AIPlayer.h"
#include "Deck.h"
//#include "Card.h"

const float BJ_MULTIPLIER = 1.5;
const int TWENTY_ONE = 21;
const int SEVEN_TEEN = 17;

class Game
{
public:
	Game();
	~Game();
	void PlayGame();
	//enum option{BET, Hit};
private:
	Deck* gameDeck;
	AIPlayer* dealer;
	Player* gamePlayer;
	int curBet;
	int optionNum;
	bool isHitting;
	bool isSplited;
	bool isPlayerFinished;
	bool hasInsurance;
	int insuranceAmount;

	void Bet();
	void Hit(Player*);
	void Double();
	void Split();
	void Surrender();
	void BuyInsurance();
	void CheckWinner();
	void CheckBlackJack(Player*);
	bool CheckFiveDragon();
	void ShowTable();
	void GiveTwoCard();
	void ListOption();
	int ExcuteOption();
	//void Insurance();
};