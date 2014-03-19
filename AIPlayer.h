//AIPlayer.h
#include "Player.h"

class AIPlayer : public Player
{
public:
	AIPlayer();
	~AIPlayer();
	void PrintCards(bool);
	bool IsAceFaceUp();
};