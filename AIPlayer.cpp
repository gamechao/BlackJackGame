//AIPlayer.cpp
#include "AIPlayer.h"

AIPlayer::AIPlayer():Player(0,0,"Dealer",1000)
{
	
}

void AIPlayer::PrintCards(bool isNotHide)
{
	int lastPos = currentPos - 1;
	for (int i = lastPos; i >=0 ; --i)
	{
		if (!isNotHide && i == 1)
		{
			std::cout << " " << "XX" << ",";
		}
		else
		std::cout << " " << playerCards[0][i]->GetVisualCard() << ",";
	}
}

bool AIPlayer::IsAceFaceUp()
{
	return (playerCards[0][0]->GetRank() == Card::ACE);
}