//Player.cpp
#include "Player.h"
#include <string>
#include <iostream>

const int ACE_FIXER = 10;

Player::Player(unsigned int curPos, unsigned int curHand, std::string playerName, int chip) : currentPos(curPos), currentHand(curHand), name(playerName), playerChip(chip)
{
	isBlackJack = false;
	isBusted = false;
	playerCards = new Card**[PLAYER_MAX_HANDS];
	for (int i = 0; i < PLAYER_MAX_HANDS; ++i)
	{
		playerCards[i] = new Card*[MAX_PLAYER_CARDS];
		for (int l = 0; l < MAX_PLAYER_CARDS; ++l)
		{
			playerCards[i][l] = nullptr;
		}
	}
}

Player::~Player()
{}

void Player::ResetPlayer()
{
	currentPos = 0;
	currentHand = 0;
	isBlackJack = false;
	isBusted = false;
}

bool Player::IsPlayerEmpty()
{
	return (currentPos < 0);
}

bool Player::IsPlayerFull()
{
	return (currentPos >= MAX_PLAYER_CARDS);
}

bool Player::IsPlayerBJ()
{
	return isBlackJack;
}

bool Player::IsPlayerBusted()
{
	return isBusted;
}

void Player::ReceiveCard(Card* handCard)
{
	if (!IsPlayerFull())
	{
		playerCards[currentHand][currentPos++] = handCard;
	}
}

unsigned int Player::CalculateTotal() 
{
	int total = 0;
	if (playerCards[currentHand][0]->GetCardValue() > 0)
	{
		int lastPos = currentPos - 1;
		bool hasAce = false;
		for (int i = lastPos; i >= 0; --i)
		{
			if (playerCards[currentHand][i]->GetCardValue() == Card::ACE)
			{
				hasAce = true;
			}
			total += playerCards[currentHand][i]->GetCardValue();
		}

		if (hasAce == true && total <= 11)
		{
			total += ACE_FIXER;
		}

		if (hasAce == true && total == 21 && currentPos == 2)
		{
			isBlackJack = true;
		}
		else
		{
			isBlackJack = false;
		}
	}

	if (total > 21)
	{
		isBusted = true;
	}

	return total;
}

void Player::PrintCards()
{
	int lastPos = currentPos - 1;
	for (int i = lastPos; i >=0 ; --i)
	{
		std::cout << " " << playerCards[currentHand][i]->GetVisualCard() << ",";
	}
	std::cout << "\n";
}

void Player::UpdateChip(int amount)
{
	playerChip += amount;
	if (playerChip<0)
	{
		playerChip = 0;
	}
}

int Player::GetChip()
{
	return playerChip;
}

void Player::Split()
{
	playerCards[1][0] = playerCards[0][1];
	playerCards[0][1] = nullptr;
	currentPos--;
}

void Player::ChangeHand()
{
	currentHand++;
	currentPos = 1;
}

void Player::ToggleHand(int handNum)
{
	currentHand = handNum;
	currentPos = 0;
	for (int i = 0; i < MAX_PLAYER_CARDS; i++)
	{
		if (playerCards[currentHand][i] != nullptr)
		{
			currentPos++;
		}
		else
		{
			break;
		}
	}
}

void Player::SetPlayerSplit()
{
	if(playerCards[0][0]->GetRank() == playerCards[0][1]->GetRank())
	{
		canSplit = true;
	}
	else
	{
		canSplit = false;
	}
}

bool Player::GetPlayerSplit()
{
	return canSplit;
}

void Player::ClearCards()
{
	for (int i = 0; i < PLAYER_MAX_HANDS; ++i)
	{
		playerCards[i] = new Card*[MAX_PLAYER_CARDS];
		for (int l = 0; l < MAX_PLAYER_CARDS; ++l)
		{
			playerCards[i][l] = nullptr;
		}
	}
	ResetPlayer();
}