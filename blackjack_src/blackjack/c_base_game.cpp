#include "c_base_game.h"

void CBaseGame::CreateSaveFolder()
{
	std::filesystem::path fsPath("C:\\Program Files\\Blackjack");
	std::filesystem::permissions(fsPath, std::filesystem::perms::all);

	if (std::filesystem::exists(fsPath))
		return;

	std::filesystem::create_directories(fsPath);
}

void CBaseGame::InitSave(CStatManager* statmanager)
{
	float nBalance = 0;
	float nWins = 0;
	float nLosses = 0;

	if (this->GetSaveStatus())
	{
		return;
	}

	if (!this->m_ifSave.is_open())
	{
		this->m_ifSave.open(m_szFileName, std::ifstream::in);
	}

	if (this->m_ifSave.peek() == std::ifstream::traits_type::eof())
	{
		this->m_ifSave.close();
		this->SetSaveStatus(true);
	}
	else
	{
		this->m_ifSave >> nBalance >> nWins >> nLosses;
		this->m_ifSave.close();
		statmanager->SetBalance((int)(nBalance / PI));
		statmanager->SetWins((int)(nWins / PI));
		statmanager->SetLosses((int)(nLosses / PI));
		this->SetSaveStatus(true);
	}
	
	this->SetSaveStatus(true);
}

void CBaseGame::WriteSave(CStatManager* statmanager)
{
	if (!m_ofSave.is_open())
	{
		this->m_ofSave.open(m_szFileName, std::ofstream::out);
		this->m_ofSave << (float)(statmanager->GetBalance() * PI) << "\n" << (float)(statmanager->GetWins() * PI) << "\n" << (float)(statmanager->GetLosses() * PI);
		this->m_ofSave.close();
	}
	else
	{
		this->m_ofSave << (float)(statmanager->GetBalance() * PI) << "\n" << (float)(statmanager->GetWins() * PI) << "\n" << (float)(statmanager->GetLosses() * PI);
		this->m_ofSave.close();
	}
}

void CBaseGame::StartManager()
{
	std::string szString;
	std::cin >> szString;

	if (szString == "start")
	{
		this->SetState(STATE_BET);
	}
	else
	{
		this->SetState(STATE_PRE);
	}
}

void CBaseGame::BetManager(CStatManager* statmanager)
{
	int nBet;
	std::cin >> nBet;

	if (std::cin.good())
	{
		if (nBet > statmanager->GetBalance() || nBet < 1)
			return;

		this->SetBet(nBet);
		this->SetState(STATE_IN);
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		this->SetState(STATE_BET);
	}
}

void CBaseGame::RestartManager(CBasePlayer* player, CBaseDealer* dealer, CBaseGUI* gui, CStatManager* statmanager)
{
	bool bShouldReset = false;
	std::string szString;
	std::cin >> szString;

	if (szString == "restart")
	{
		bShouldReset = true;
	}
	else
	{
		bShouldReset = false;
	}

	if (bShouldReset)
	{
		delete(player);
		this->SetState(STATE_PRE);
		this->Game(statmanager);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}

void CBaseGame::Cmp(CBasePlayer* player, CBaseDealer* dealer)
{
	if (player->GetHand() > 21)
	{
		this->SetState(STATE_END);
		player->SetResult(RESULT_LOSE);
		return;
	}

	if (dealer->GetHand() > 21)
	{
		this->SetState(STATE_END);
		player->SetResult(RESULT_WIN);
		return;
	}

	if (player->GetHand() == 21)
	{
		this->SetState(STATE_END);
		player->SetResult(RESULT_WIN);
		return;
	}

	if (dealer->GetHand() == 21)
	{
		this->SetState(STATE_END);
		player->SetResult(RESULT_LOSE);
		return;
	}

	if (player->GetInput() == INPUT_STAND && dealer->GetInput() == INPUT_STAND)
	{
		if (player->GetHand() > dealer->GetHand())
		{
			this->SetState(STATE_END);
			player->SetResult(RESULT_WIN);
		}
		else if (player->GetHand() < dealer->GetHand())
		{
			this->SetState(STATE_END);
			player->SetResult(RESULT_LOSE);
		}
		else if (player->GetHand() == dealer->GetHand())
		{
			this->SetState(STATE_END);
			player->SetResult(RESULT_DRAW);
		}
	}
}

void CBaseGame::Mechanics(CBasePlayer* player, CStatManager* statmanager)
{
	if (player->GetResult() == RESULT_WIN)
	{
		statmanager->SetWins(statmanager->GetWins() + 1);

		if (player->GetDoubleDown())
		{
			statmanager->SetBalance(statmanager->GetBalance() + this->GetBet() * 2);
		}
		else
		{
			statmanager->SetBalance(statmanager->GetBalance() + this->GetBet());
		}
	}
	else if (player->GetResult() == RESULT_LOSE)
	{
		statmanager->SetLosses(statmanager->GetLosses() + 1);

		if (player->GetDoubleDown())
		{
			statmanager->SetBalance(statmanager->GetBalance() - this->GetBet() * 2);
		}
		else
		{
			statmanager->SetBalance(statmanager->GetBalance() - this->GetBet());
		}
	}
}

void CBaseGame::Game(CStatManager* pStatManager)
{
	CBasePlayer* pPlayer = new CBasePlayer();
	CBaseDealer* pDealer = new CBaseDealer();
	CBaseGUI* pGUI = new CBaseGUI();

	this->CreateSaveFolder();
	this->InitSave(pStatManager);

	pPlayer->GenerateHand();
	pDealer->GenerateHand();

	pGUI->PrepareWindow();

	while (true)
	{
		switch (this->GetState())
		{
		case STATE_PRE:
		{
			pGUI->PrintGUI(pPlayer, pDealer, pStatManager, this->GetState());
			this->StartManager();
		} break;
		case STATE_BET:
		{
			pGUI->PrintGUI(pPlayer, pDealer, pStatManager, this->GetState());
			this->BetManager(pStatManager);
		} break;
		case STATE_IN:
		{
			this->Cmp(pPlayer, pDealer);
			pGUI->PrintGUI(pPlayer, pDealer, pStatManager, this->GetState());
			pPlayer->Play();
			pDealer->Play(*pPlayer);
			this->Cmp(pPlayer, pDealer);
		} break;
		case STATE_END:
		{
			pGUI->PrintGUI(pPlayer, pDealer, pStatManager, this->GetState());
			this->Mechanics(pPlayer, pStatManager);
			this->WriteSave(pStatManager);
			this->RestartManager(pPlayer, pDealer, pGUI, pStatManager);
		} break;
		}
	}
}