#pragma once

enum CardSuits
{
	CARD_CLUBS = 1,
	CARD_HEARTS = 2,
	CARD_SPADES = 3,
	CARD_DIAMONDS = 4
};

enum CardTypes
{
	CARD_NORMAL = 1,
	CARD_JACK = 2,
	CARD_QUEEN = 3,
	CARD_KING = 4,
	CARD_ACE = 5
};

struct Card_t
{
	int m_nCardValue = 0; //the value the card will have
	int m_iCardSuit = 0;  //will be used to display theses cards, not actually useful for anything else
	int m_iCardType = 0;  //will be used to display theses cards, not actually useful for anything else
};