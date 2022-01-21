#include "c_base_player.h"

void CBasePlayer::ParseInput()
{
	std::string szString;
	std::cin >> szString;

	if (szString == "hit")
	{
		this->SetInput(INPUT_HIT);
	}
	else if (szString == "stand")
	{
		this->SetInput(INPUT_STAND);
	}
	else if (szString == "dd")
	{
		this->SetInput(INPUT_DOUBLEDOWN);
	}
	else
	{
		this->SetInput(INPUT_NONE);
	}
}

void CBasePlayer::Play()
{
	this->ParseInput();

	switch (this->GetInput())
	{

	case INPUT_NONE:
	{
		
	} break;

	case INPUT_HIT:
	{
		int nCard = this->GenerateCard();
		this->SetHand(this->GetHand() + nCard);
		this->SetHit(true);
	} break;

	case INPUT_STAND:
	{
		
	} break;

	case INPUT_DOUBLEDOWN:
	{
		if (this->GetHit()) 
			return;

		int nCard = this->GenerateCard();
		this->SetHand(this->GetHand() + nCard);
		this->SetInput(INPUT_STAND);
		this->SetDoubleDown(true);
	} break;

	}
}