#include "c_base_entity.h"

int CBaseEntity::GenerateCard()
{
	Card_t card;

	card.m_nCardValue = 0;

	card.m_nCardValue = Utils::GenerateRandNum(1, 10);

	if (this->GetHand() < 11 && card.m_nCardValue == 1)
	{
		card.m_nCardValue = 11;
		card.m_iCardType = CARD_ACE;
	}

	if (card.m_nCardValue == 10 && Utils::GenerateRandNum(1, 4) != 1)
	{
		card.m_iCardType = Utils::GenerateRandNum(2, 4);
	}

	card.m_iCardType = 1;
	card.m_iCardSuit = Utils::GenerateRandNum(1, 4);

	this->m_arrCards.push_front(card);

	return card.m_nCardValue;
}

void CBaseEntity::GenerateHand()
{
	int nHand = 0, nCard = 0;

	for (int i = 0; i < 2; i++)
	{
		nCard = this->GenerateCard();

		nHand += nCard;

		this->SetHand(nHand);
	}
}