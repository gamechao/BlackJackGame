//Deck.h
#pragma once
#include "Card.h"

const int MAX_CARDS = 52;

class Deck
{
public:
	Deck(unsigned int dPos = 0);
	~Deck();
	void ClearDeck();
	void PopulateDeck();
	void ShuffleDeck();
	bool IsDeckEmpty();
	void AddCardToDeck(Card* card);
	unsigned int CurrentPosition();
	Card* GiveCard();
	void PrintDeck();

private:
	unsigned int deckCurrentPos;
	Card* deckCards[MAX_CARDS];
};