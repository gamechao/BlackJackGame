//Deck.cpp
#include "Deck.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>		/* time */
#include <iostream>

Deck::Deck(unsigned int dPos)
{
	ClearDeck();
	PopulateDeck();
	ShuffleDeck();
}

Deck::~Deck()
{}

unsigned int Deck:: CurrentPosition()
{
	return deckCurrentPos;
}

void Deck::ClearDeck()
{
	deckCurrentPos = 0;
}

void Deck::PopulateDeck()
{
	for(int s = Card::HEART; s <= Card::SPADE; ++s)
	{
		for (int r = Card::ACE; r <= Card::KING; ++r)
		{
			Card* tempCard = new Card;
			tempCard->SetRank(r);
			tempCard->SetSuit(s);
			AddCardToDeck(tempCard);
		}
	}
}

void Deck::AddCardToDeck(Card* card)
{
	deckCards[deckCurrentPos++] = card;
}

void Deck::ShuffleDeck()
{
	 srand (time(0));
	 for (int i = 0; i < MAX_CARDS; ++i)
	 {
		 int r = rand()%(MAX_CARDS);
		 Card* tempCard = deckCards[i];
		 deckCards[i] = deckCards[r];
		 deckCards[r] = tempCard;
	 }
}

bool Deck::IsDeckEmpty()
{
	return (deckCurrentPos <= 0);
}

Card* Deck::GiveCard()
{
	if (IsDeckEmpty())
	{
		deckCurrentPos = MAX_CARDS;
		ShuffleDeck();
		return deckCards[--deckCurrentPos];
	}
	else
	{
		return deckCards[--deckCurrentPos];
	}
}

void Deck::PrintDeck()
{
	for (int i = 0; i < MAX_CARDS; ++i)
	{
		std::cout<< "Card num " << i << ": Rank: " << deckCards[i]->GetRank() << "Suit" << deckCards[i]->GetSuit() <<"\n";
	}
}