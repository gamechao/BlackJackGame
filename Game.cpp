//Game.cpp
#include "Game.h"
#include <iostream>
#include <string>

const int FIRST_HAND = 0;
const int SECOND_HAND = 1;
const int MAX_OPTION = 5;
const int DOUBLE_MODIFIER = 2;

enum options{HIT = 1, STAND, DOUBLE, SURRENDER, SPLIT, INSURANCE};

Game::Game()
{
	gameDeck = new Deck(0);
	dealer = new AIPlayer();
	gamePlayer = new Player(0, 0, "Player", 1000);
	isHitting = false;
	isPlayerFinished = false;
	hasInsurance = false;
}

void Game::Bet()
{
	std::cout << "Please type in the number you want to bet(1 - " << gamePlayer->GetChip() << "):";
	int tempBet;
	std::cin >> tempBet;
	while (tempBet > gamePlayer->GetChip() || tempBet <= 0)
	{
		std::cout << "Invalid number! Please retype the number you want to bet (1 - " << gamePlayer->GetChip() << "):";
		std::cin >> tempBet;
	}
	curBet = tempBet;
}

void Game::Hit(Player* curPlayer)
{
	if (!curPlayer->IsPlayerFull())
	{
		curPlayer->ReceiveCard(gameDeck->GiveCard());
		isHitting = true;
	}
	else
	{
		std::cout << "You have Full Card!/n" << curPlayer->IsPlayerFull();
	}
}

void Game::Double()
{
	curBet *= DOUBLE_MODIFIER; 
	gamePlayer->ReceiveCard(gameDeck->GiveCard());
}

void Game::Split()
{
	isSplited = true;
	gamePlayer->Split();
	gamePlayer->ReceiveCard(gameDeck->GiveCard());
	gamePlayer->SetPlayerSplit();
}

void Game::Surrender()
{
	curBet = static_cast<int>(curBet/DOUBLE_MODIFIER);
	gamePlayer->UpdateChip(-curBet);
	dealer->UpdateChip(curBet);
}

void Game::BuyInsurance()
{
	insuranceAmount = static_cast<int>(curBet/DOUBLE_MODIFIER);
	hasInsurance = true;
	curBet =  insuranceAmount;
}

void Game::ListOption()
{
	if (isHitting)
	{
		std::cout << "Here are the options: 1.Hit 2.Stand  \n"; 
	}
	else
	{
		std::cout << "Here are the options: 1.Hit 2.Stand 3.Double 4.Surrender ";
		if (gamePlayer->GetPlayerSplit())
		{
			std::cout << "5.split "; 
		}
		std::cout << "\n";
	}
	
}

int Game::ExcuteOption()
{
	int option;
	std::cin >> option;
	while (option < 0 ||option > MAX_OPTION)
	{
		std::cout << "Invalid option! Please enter a valid number.\n";
		std::cin >> option;
	}
	options tempOption;
	tempOption = static_cast<options>(option);
	switch(tempOption)//[???]wondering besides int and char what else can be taken as the case in switch
	{
	case HIT:
		Hit(gamePlayer);
		break;
	case STAND:
		break;
	case DOUBLE:
		Double();
		break;
	case SURRENDER:
		Surrender();
		break;
	case SPLIT:
		Split();
		break;
	default:
		break;
	}
	return option;
}

void Game::CheckBlackJack(Player* curPlayer)
{
	if (curPlayer == dealer)
	{
		std::cout << "Dealer has Black Jack, Dealer wins!\n";
		gamePlayer->UpdateChip(-curBet);
		dealer->UpdateChip(curBet);
	}
	else if (curPlayer == gamePlayer)
	{
		std::cout << "You have Black Jack, You win!\n";
		gamePlayer->UpdateChip(static_cast<int>(curBet * BJ_MULTIPLIER));
		dealer->UpdateChip(static_cast<int>(-curBet * BJ_MULTIPLIER));
	}
}

bool Game::CheckFiveDragon()
{
	bool hasFiveDragon = false;
	dealer->CalculateTotal();
	gamePlayer->CalculateTotal();
	if (dealer->IsPlayerBusted() == false && dealer->IsPlayerFull() == true && gamePlayer->IsPlayerFull() == false)
	{
		std::cout << "Dealer has Five Dragon, Dealer wins!\n";
		gamePlayer->UpdateChip(-curBet);
		dealer->UpdateChip(curBet);
		hasFiveDragon = true;
	}
	else if (gamePlayer->IsPlayerFull() == true && dealer->IsPlayerFull() == true)
	{
		if (gamePlayer->IsPlayerBusted() == true && dealer->IsPlayerBusted() == false)
		{
			std::cout << "Dealer has Five Dragon and you busted, Dealer wins!\n";
			gamePlayer->UpdateChip(-curBet);
			dealer->UpdateChip(curBet);
		}
		else if (gamePlayer->IsPlayerBusted() == false && dealer->IsPlayerBusted() == true)
		{
			std::cout << "You have Five Dragon and dealer busted, You win!\n";
			gamePlayer->UpdateChip(static_cast<int>(curBet * BJ_MULTIPLIER));
			dealer->UpdateChip(static_cast<int>(-curBet * BJ_MULTIPLIER));
		}
		else
		{
			std::cout << "Push!\n";
		}
		hasFiveDragon = true;
	}
	else if (gamePlayer->IsPlayerBusted() == false && gamePlayer->IsPlayerFull() == true && dealer->IsPlayerFull() == false)
	{
		std::cout << "You have Five Dragon, You win!\n";
		gamePlayer->UpdateChip(static_cast<int>(curBet * BJ_MULTIPLIER));
		dealer->UpdateChip(static_cast<int>(-curBet * BJ_MULTIPLIER));
		hasFiveDragon = true;
	}
	else
	{
		hasFiveDragon = false;
	}
	return hasFiveDragon;
}

void Game::CheckWinner()
{
	if (CheckFiveDragon() == false)
	{
		if (dealer->CalculateTotal() > gamePlayer->CalculateTotal())
		{
			if (gamePlayer->IsPlayerBusted())
			{
				std::cout << "Push!\n";
			}
			else if (dealer->IsPlayerBusted() && !gamePlayer->IsPlayerBusted())
			{
				std::cout << "Dealer busts, You win!\n";
				gamePlayer->UpdateChip(curBet);
				dealer->UpdateChip(-curBet);
			}
			else if (!dealer->IsPlayerBusted() || !gamePlayer->IsPlayerFull())
			{
				std::cout << "Dealer has greater number, Dealer wins!\n";
				gamePlayer->UpdateChip(-curBet);
				dealer->UpdateChip(curBet);
			}


		}
		else if (dealer->CalculateTotal() < gamePlayer->CalculateTotal())
		{
			if (!gamePlayer->IsPlayerBusted())
			{
				std::cout << "You have greater number, You win!\n";
				gamePlayer->UpdateChip(curBet);
				dealer->UpdateChip(-curBet);
			}
			else if (gamePlayer->IsPlayerBusted() && !dealer->IsPlayerBusted())
			{
				std::cout << "You busts, Dealer wins!\n";
				gamePlayer->UpdateChip(-curBet);
				dealer->UpdateChip(curBet);
			}
		}
		else
		{
			std::cout << "Push!\n";
		}
	}
	
	/*
	if (gamePlayer->CalculateTotal() > 21)
	{
		std::cout << "You busts, Dealer wins!\n";
		gamePlayer->UpdateChip(-curBet);
		dealer->UpdateChip(curBet);
	}
	else if (dealer->CalculateTotal() > 21)
	{
		std::cout << "Dealer busts, You win!\n";
		gamePlayer->UpdateChip(curBet);
		dealer->UpdateChip(-curBet);
	}
	else if (dealer->CalculateTotal() == gamePlayer->CalculateTotal())
	{
		std::cout << "Push!\n";
	}
	else if (dealer->CalculateTotal() > gamePlayer->CalculateTotal() || !gamePlayer->IsPlayerFull())
	{
		std::cout << "Dealer has greater number, Dealer wins!\n";
		gamePlayer->UpdateChip(-curBet);
		dealer->UpdateChip(curBet);
	}
	else if (dealer->CalculateTotal() < gamePlayer->CalculateTotal() || !dealer->IsPlayerFull())
	{
		std::cout << "You have greater number, You win!\n";
		gamePlayer->UpdateChip(curBet);
		dealer->UpdateChip(-curBet);
	}
	else if (dealer->IsPlayerBJ())
	{
		std::cout << "Dealer has Black Jack, Dealer wins!\n";
		gamePlayer->UpdateChip(-curBet);
		dealer->UpdateChip(curBet);
	}
	else if (gamePlayer->IsPlayerBJ())
	{
		std::cout << "You have Black Jack, You win!\n";
		gamePlayer->UpdateChip(static_cast<int>(curBet * BJ_MULTIPLIER));
		dealer->UpdateChip(static_cast<int>(curBet * BJ_MULTIPLIER));
	}
	else if (dealer->IsPlayerFull() && !gamePlayer->IsPlayerFull())
	{
		std::cout << "Dealer has Five Dragon, Dealer wins!\n";
		gamePlayer->UpdateChip(-curBet);
		dealer->UpdateChip(curBet);
	}
	else if (gamePlayer->IsPlayerFull() && !dealer->IsPlayerFull())
	{
		std::cout << "You have Five Dragon, You win!\n";
		gamePlayer->UpdateChip(static_cast<int>(curBet * BJ_MULTIPLIER));
		dealer->UpdateChip(static_cast<int>(curBet * BJ_MULTIPLIER));
	}
	*/
}

void Game::ShowTable()
{
	std::cout << "Dealer has ";
	dealer->PrintCards(isPlayerFinished); 
	std::cout << "\n";
	std::cout << "You have ";
	gamePlayer->PrintCards();
	std::cout << "\n";
}

void Game::GiveTwoCard()
{
	dealer->ReceiveCard(gameDeck->GiveCard());
	dealer->ReceiveCard(gameDeck->GiveCard());
	gamePlayer->ReceiveCard(gameDeck->GiveCard());
	gamePlayer->ReceiveCard(gameDeck->GiveCard());
}

void Game::PlayGame()
{
	std::cout << "Welcome to Black Jack Game! Enjoy!\n";
	int continueFlag = 1;
	while (continueFlag)
	{
		int option =0;
		isPlayerFinished = false;
		isHitting = false;
		std::cout << "Dealer has " << dealer->GetChip() << "chips, "
				  << "You have " << gamePlayer->GetChip() << "chips.\n";
		Bet();
		GiveTwoCard();
		ShowTable();
		if (dealer->IsAceFaceUp())
		{
			std::cout << "Do you want to buy Insurance? Type 0 for NO, 1 for YES\n";
			int inputNum;
			std::cin >> inputNum;
			if (inputNum == 1)
			{
				BuyInsurance();
			}
			else
			{
				while(inputNum != 0)
				{
					std::cout << "Invalid input please retype! Type 0 for NO, 1 for YES\n";
					std::cin >> inputNum; 
				}
			}
		}
		gamePlayer->SetPlayerSplit();
		gamePlayer->CalculateTotal();
		dealer->CalculateTotal();
		
		if (gamePlayer->IsPlayerBJ() == true)
		{
			if (dealer->IsPlayerBJ() == false)
			{
				CheckBlackJack(gamePlayer);
			}
			else
			{
				std::cout << "Push!\n";
			}
		}
		else if (dealer->IsPlayerBJ() == true)
		{
			if (hasInsurance)
			{
				gamePlayer->UpdateChip(insuranceAmount * DOUBLE_MODIFIER);
				dealer->UpdateChip(insuranceAmount * DOUBLE_MODIFIER);
				std::cout << "Dealer is Black Jack, Player get insurance!\n";
			}

			if (gamePlayer->IsPlayerBJ() == false)
			{
				CheckBlackJack(dealer);
			}
			else
			{
				std::cout << "Push!\n";
			}
		}
		else
		{
			ListOption();
			option = ExcuteOption();
			if (option == SURRENDER)
			{
				std::cout << "You surrendered!\n";
			}
			else
			{
				gamePlayer->CalculateTotal();
				ShowTable();
				if (isSplited == true)
				{
					std::cout << "Now start with the first hand:\n";
					std::cout << "First Hand Card: ";
					gamePlayer->PrintCards();
					std::cout << "\n";
					if (hasInsurance)
					{
						gamePlayer->UpdateChip(insuranceAmount);
						dealer->UpdateChip(insuranceAmount);
						std::cout << "Dealer is not Black Jack, Player lose insurance!\n";
					}
					if (gamePlayer->IsPlayerBJ())
					{
						CheckBlackJack(gamePlayer);
					}
					else
					{
						ListOption();
						option = ExcuteOption();
						std::cout << "First Hand:\n";
						ShowTable();
						while (option == 1)
						{
							ListOption();
							option = ExcuteOption();
							ShowTable();
							if (gamePlayer->IsPlayerBusted() == true)
								break;
						}
					}
					gamePlayer->ChangeHand();
					std::cout << "Now start with the second hand:\n";
					gamePlayer->ReceiveCard(gameDeck->GiveCard());
					gamePlayer->CalculateTotal();
					std::cout << "Second Hand Card: ";
					gamePlayer->PrintCards();
					std::cout << "\n";
					if (gamePlayer->IsPlayerBJ())
					{
						CheckBlackJack(gamePlayer);
					}
					else
					{
						ListOption();
						option = ExcuteOption();
						std::cout << "Second Hand:\n";
						ShowTable();
						while (option == 1)
						{
							ListOption();
							option = ExcuteOption();
							ShowTable();
							if (gamePlayer->IsPlayerBusted() == true)
								break;
						}
					}
					isPlayerFinished = true;
				}
				else
				{
					while (option == 1)
					{		
						if (gamePlayer->IsPlayerBusted() == false)
						{
							ListOption();
							option = ExcuteOption();
							gamePlayer->CalculateTotal();
							ShowTable();
						}
						else
						{
							option = 2;
						}
					}
					isPlayerFinished = true;
				}
																			/*
			if (gamePlayer->IsPlayerBusted() == false && dealer->CalculateTotal() < gamePlayer->CalculateTotal())
			{
				while(dealer->IsPlayerFull() == false)
				{
					if (dealer->IsPlayerBusted() == false && dealer->CalculateTotal() < gamePlayer->CalculateTotal())
					{

						Hit(dealer);
						ShowTable();
					}
					else
					{
						break;
					}
				}
			}*/
				if (gamePlayer->IsPlayerBusted() == false)
				{
					while (dealer->IsPlayerFull() == false && dealer->CalculateTotal() < SEVEN_TEEN)
					{
						Hit(dealer);
					}
					ShowTable();
				}
				else
				{
					ShowTable();
				}
				std::cout << " dealer's total: " << dealer->CalculateTotal() << "\n";
				std::cout << " player's total: " << gamePlayer->CalculateTotal() << "\n";
				if (isSplited == true)
				{
				
					std::cout << " dealer's total: " << dealer->CalculateTotal() << "\n";
					gamePlayer->ToggleHand(FIRST_HAND);
					std::cout << " player's first hand total: " << gamePlayer->CalculateTotal() << "\n";
					if (gamePlayer->IsPlayerBJ() == false)
					{
						CheckWinner();
					}
					std::cout << " dealer's total: " << dealer->CalculateTotal() << "\n";
					gamePlayer->ToggleHand(SECOND_HAND);
					std::cout << " player's second hand total: " << gamePlayer->CalculateTotal() << "\n";
					if (gamePlayer->IsPlayerBJ() == false)
					{
						CheckWinner();
					}
				}
				else
				{
					CheckWinner();
				}
			}
			
		}
		isSplited = false;
		dealer->ClearCards();
		gamePlayer->ClearCards();
		gameDeck->ClearDeck();
		gameDeck->PopulateDeck();
		gameDeck->ShuffleDeck();
	}
	

}