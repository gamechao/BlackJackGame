//Card.h
#pragma  once
#include <iostream>
#include <string>

class Card
{
public:
	enum rank{ACE = 1, TWO, THREE, FOUR, FIVE, SIX,SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
	enum suit{HEART, DIAMOND, CLUB, SPADE};
	Card();
	Card(rank,suit);
	~Card();
	unsigned int GetCardValue() const;
	void FlipCard();
	rank GetRank();
	suit GetSuit();
	void SetRank(int);
	void SetSuit(int);
	std::string GetVisualCard();

private:
	rank cardRank;
	suit cardSuit;
	std::string visualCard;
};