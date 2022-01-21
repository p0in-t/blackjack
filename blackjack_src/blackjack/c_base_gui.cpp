#include "c_base_gui.h"

void CBaseGUI::PrepareWindow()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 20;
	cfi.dwFontSize.Y = 25;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");

	SetConsoleDisplayMode(console, CONSOLE_FULLSCREEN_MODE, &pos);
	SetCurrentConsoleFontEx(console, false, &cfi);
}

void PrintDeck(std::deque<Card_t>& deque)
{
	for (unsigned int i = 0; i < deque.size(); i++)
	{
		if (i == deque.size() - 1)
		{
			std::cout << deque.at(i).m_nCardValue;
		}
		else
		{
			std::cout << deque.at(i).m_nCardValue << ", ";
		}
	}
}

std::string GetCardSuit(CBaseEntity* entity)
{
	switch (entity->m_arrCards.front().m_iCardSuit)
	{

	case CARD_CLUBS:
	{
		return "Club";
	} break;

	case CARD_HEARTS:
	{
		return "Heart";
	} break;

	case CARD_SPADES:
	{
		return "Spade";
	} break;

	case CARD_DIAMONDS:
	{
		return "Diamond";
	} break;

	default:
	{
		return "Error";
	} break;

	}
}

std::string GetCardType(CBaseEntity* entity)
{
	switch (entity->m_arrCards.front().m_iCardType)
	{

	case CARD_NORMAL:
	{
		return "10";
	} break;

	case CARD_JACK:
	{
		return "Jack";
	} break;

	case CARD_QUEEN:
	{
		return "Queen";
	} break;

	case CARD_KING:
	{
		return "King";
	} break;

	case CARD_ACE:
	{
		return "Ace";
	} break;

	default:
	{
		return "Error";
	} break;

	}
}

void CBaseGUI::PrintGUI(CBasePlayer* player, CBaseDealer* dealer, CStatManager* statmanager, int state)
{
	switch (state)
	{

	case STATE_NONE:
	{
		
	} break;

	case STATE_PRE:
	{
		system("cls");

		std::cout << "Welcome to blackjack!\n\n";
		std::cout << "Balance : " << statmanager->GetBalance() << "\n";
		std::cout << "Wins : " << statmanager->GetWins() << "\n";
		std::cout << "Losses : " << statmanager->GetLosses() << "\n\n";
		std::cout << "Controls :\n";
		std::cout << "To start the game, type : 'start'\n";
		std::cout << "To hit, type : 'hit'\n";
		std::cout << "To stand, type : 'stand'\n";
		std::cout << "To double down, type : 'dd'\n\n";
		std::cout << "Good luck!\n\n";
	} break;

	case STATE_BET:
	{
		system("cls");

		std::cout << "Balance : " << statmanager->GetBalance() << "\n";
		std::cout << "How much do you want to bet?\n\n";
	} break;

	case STATE_IN:
	{
		system("cls");
		
		std::cout << "Players hand : " << player->GetHand() << " (";
		PrintDeck(player->m_arrCards);
		std::cout << ") New card : " << player->m_arrCards.front().m_nCardValue;
		std::cout << " | Card suit : " << GetCardSuit(player) << "\n";

		std::cout << "Dealers hand : " << dealer->GetHand() << " (";
		PrintDeck(dealer->m_arrCards);
		std::cout << ") New card : " << dealer->m_arrCards.front().m_nCardValue;
		std::cout << " | Card suit : " << GetCardSuit(dealer) << "\n\n";
	} break;

	case STATE_END:
	{
		system("cls");

		if (player->GetResult() == RESULT_WIN)
		{
			std::cout << "You win!\n";
			std::cout << "Players hand : " << player->GetHand() << " (";
			PrintDeck(player->m_arrCards);
			std::cout << ") New card : " << player->m_arrCards.front().m_nCardValue;
			std::cout << " | Card suit : " << GetCardSuit(player) << "\n";
			std::cout << "Dealers hand : " << dealer->GetHand() << " (";
			PrintDeck(dealer->m_arrCards);
			std::cout << ") New card : " << dealer->m_arrCards.front().m_nCardValue;
			std::cout << " | Card suit : " << GetCardSuit(dealer) << "\n";
			std::cout << "Type 'restart' to play again!\n\n";
		}
		else if (player->GetResult() == RESULT_LOSE)
		{
			std::cout << "You lose!\n";
			std::cout << "Players hand : " << player->GetHand() << " (";
			PrintDeck(player->m_arrCards);
			std::cout << ") New card : " << player->m_arrCards.front().m_nCardValue;
			std::cout << " | Card suit : " << GetCardSuit(player) << "\n";
			std::cout << "Dealers hand : " << dealer->GetHand() << " (";
			PrintDeck(dealer->m_arrCards);
			std::cout << ") New card : " << dealer->m_arrCards.front().m_nCardValue;
			std::cout << " | Card suit : " << GetCardSuit(dealer) << "\n";
			std::cout << "Type 'restart' to play again!\n\n";
		}
		else if (player->GetResult() == RESULT_DRAW)
		{
			std::cout << "Draw!\n";
			std::cout << "Players hand : " << player->GetHand() << " (";
			PrintDeck(player->m_arrCards);
			std::cout << ") New card : " << player->m_arrCards.front().m_nCardValue;
			std::cout << " | Card suit : " << GetCardSuit(player) << "\n";
			std::cout << "Dealers hand : " << dealer->GetHand() << " (";
			PrintDeck(dealer->m_arrCards);
			std::cout << ") New card : " << dealer->m_arrCards.front().m_nCardValue;
			std::cout << " | Card suit : " << GetCardSuit(dealer) << "\n";
			std::cout << "Type 'restart' to play again!\n\n";
		}
	} break;

	}
}