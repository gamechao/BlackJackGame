//Card.cpp
#include "Card.h"
#include <string>
#include <iostream>
#include <stdio.h>

Card::Card()
{

}

Card::Card(rank r, suit s)
{}

Card::~Card()
{}


unsigned int Card::GetCardValue() const
{
	int cardValue = 0;

	cardValue = cardRank;
	if(cardValue > 10)
		cardValue = 10;

	return cardValue;	
}

void Card::FlipCard()
{
	
}

Card::rank Card::GetRank()
{
	return cardRank;
}

Card::suit Card::GetSuit()
{
	return cardSuit;
}

void Card::SetRank(int r)
{
	cardRank = static_cast<Card::rank>(r);
}

void Card::SetSuit(int s)
{
	cardSuit = static_cast<Card::suit>(s);
}

std::string Card::GetVisualCard()
{
	std::string tempRank,tempSuit;

	if (cardRank == Card::ACE)
	{
		tempRank = "A";
	}
	else if (cardRank == Card::JACK)
	{
		tempRank = "J";
	}
	else if (cardRank == Card::QUEEN)
	{
		tempRank = "Q";
	}
	else if (cardRank == Card::KING)
	{
		tempRank = "K";
	}
	else
	{
		//this is so weird that i have to declear rank as long long to avoid getting a  'std::to_string' : ambiguous call to overloaded function error
		long long transRank = static_cast<int>(cardRank);
		tempRank = std::to_string(transRank);
	}

	if (cardSuit == Card::HEART)
	{
		tempSuit = "H";
	}
	else if (cardSuit == Card::DIAMOND)
	{
		tempSuit = "D";
	}
	else if (cardSuit == Card::CLUB)
	{
		tempSuit = "C";
	}
	else if (cardSuit == Card::SPADE)
	{
		tempSuit = "S";
	}

	visualCard = tempSuit + tempRank;
	return visualCard;
}