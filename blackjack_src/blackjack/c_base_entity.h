#pragma once
#include "includes.h"
#include "c_base_card.h"

enum Inputs
{
	INPUT_NONE = 0,
	INPUT_HIT = 1,
	INPUT_STAND = 2,
	INPUT_DOUBLEDOWN = 3,
};

enum Results
{
	RESULT_NONE = 0,
	RESULT_WIN = 1,
	RESULT_LOSE = 2,
	RESULT_DRAW = 3,
};

class CBaseEntity
{
public:
	bool GetIsDealer() { return m_bIsDealer; };
	void SetIsDealer(bool value) { m_bIsDealer = value; };

	int GetInput() { return m_iInput; };
	void SetInput(int value) { m_iInput = value; };

	int GetResult() { return m_iResult; };
	void SetResult(int value) { m_iResult = value; };

	int GenerateCard();
	void GenerateHand();

	int GetHand() { return m_nHand; };
	void SetHand(int value) { m_nHand = value; };

	std::deque<Card_t> m_arrCards;
private:
	int m_iResult = RESULT_NONE;
	int m_iInput = INPUT_NONE;
	int m_nHand = 0;
	bool m_bIsDealer;
};