#include "c_base_dealer.h"

void CBaseDealer::Play(CBasePlayer player)
{
	if (player.GetInput() != INPUT_STAND || this->GetInput() == INPUT_STAND)
		return;

	while (this->GetHand() < 17)
	{
		int nCard = this->GenerateCard();
		this->SetHand(this->GetHand() + nCard);
	}

	this->SetInput(INPUT_STAND);
}