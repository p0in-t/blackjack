#pragma once
#include "c_stat_manager.h"
#include "c_base_gui.h"
#include "c_base_player.h"
#include "c_base_dealer.h"

class CBaseGame
{
public:
	void CreateSaveFolder();
	void InitSave(CStatManager* statmanager);
	void WriteSave(CStatManager* statmanager);
	void StartManager();
	void BetManager(CStatManager* statmanager);
	void RestartManager(CBasePlayer* player, CBaseDealer* dealer, CBaseGUI* gui, CStatManager* statmanager);
	void Cmp(CBasePlayer* player, CBaseDealer* dealer);
	void Mechanics(CBasePlayer* player, CStatManager* statmanager);
	void Game(CStatManager* statmanager);

	int GetBet() { return m_nBet; };
	void SetBet(int value) { m_nBet = value; };

	int GetState() { return m_iGameState; };
	void SetState(int value) { m_iGameState = value; };

	bool GetSaveStatus() { return m_bHasInitialedSave; };
	void SetSaveStatus(bool value) { m_bHasInitialedSave = value; };

	bool GetFolderStatus() { return m_bHasCreatedFolder; };
	void SetFolderStatus(bool value) { m_bHasCreatedFolder = value; };

	std::ofstream m_ofSave;
	std::ifstream m_ifSave;
private:
	std::string m_szFileName = "C:\\Program Files\\Blackjack\\Save.txt";
	bool m_bHasCreatedFolder = false;
	bool m_bHasInitialedSave = false;
	int m_nBet = 0;
	int m_iGameState = STATE_PRE;
};