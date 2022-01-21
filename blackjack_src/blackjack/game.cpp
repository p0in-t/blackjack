#include "c_base_game.h"

int main()
{
	CStatManager* pStatManager = new CStatManager();
	CBaseGame* pGame = new CBaseGame();
	pGame->Game(pStatManager);

	return 0;
}