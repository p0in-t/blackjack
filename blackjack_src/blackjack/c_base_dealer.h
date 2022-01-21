#pragma once
#include "c_base_player.h"

class CBaseDealer : public CBaseEntity
{
public:
	CBaseDealer()
	{
		this->SetIsDealer(true);
	};

	void Play(CBasePlayer player);
private:

};