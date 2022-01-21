#pragma once

class CStatManager
{
public:
	int GetBalance() { return m_nBalance; };
	void SetBalance(int value) { m_nBalance = value; };

	int GetLosses() { return m_nLosses; };
	void SetLosses(int value) { m_nLosses = value; };

	int GetWins() { return m_nWins; };
	void SetWins(int value) { m_nWins = value; };
private:
	int m_nBalance = 100;
	int m_nLosses = 0;
	int m_nWins = 0;
};

