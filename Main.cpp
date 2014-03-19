//Main.cpp
#include "Game.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <conio.h>

int main()
{
	Game* newGame = new Game;
	newGame->PlayGame();
	_getch();
	return 0;
}