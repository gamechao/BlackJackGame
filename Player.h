//Player.h
#pragma once
#include "Card.h"
#include <iostream>
#include <string>

const int MAX_PLAYER_CARDS = 5;
const int PLAYER_MAX_HANDS = 2;

class Player
{
public:
	Player(unsigned int, unsigned int, std::string, int);
	~Player();
	bool IsPlayerEmpty();
	bool IsPlayerFull();
	void ResetPlayer();
	void ReceiveCard(Card*);
	unsigned int CalculateTotal();
	virtual void PrintCards();
	void UpdateChip(int);
	int GetChip();
	void Split();
	void ChangeHand();
	void ToggleHand(int);
	bool IsPlayerBJ();
	bool IsPlayerBusted();
	void SetPlayerSplit();
	bool GetPlayerSplit();
	void ClearCards();

protected:
	std::string name;
	unsigned int playerChip;
	unsigned int currentPos;
	bool isBlackJack;
	bool isBusted;
	bool canSplit;
	//Card *playerHands;
	unsigned int currentHand;
	Card*** playerCards;
};