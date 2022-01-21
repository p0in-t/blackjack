#pragma once
#include "c_base_player.h"
#include "c_base_dealer.h"
#include "c_stat_manager.h"

class CBaseGUI
{
public:
	void PrepareWindow();
	void PrintGUI(CBasePlayer* player, CBaseDealer* dealer, CStatManager* statmanager, int state);
private:
};

