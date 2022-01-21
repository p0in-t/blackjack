#pragma once
#include "c_base_entity.h"

class CBasePlayer : public CBaseEntity
{
public:
	CBasePlayer()
	{
		this->SetIsDealer(false);
	};

	bool GetHit() { return m_bHit; };
	void SetHit(bool value) { m_bHit = value; };

	bool GetDoubleDown() { return m_bDidDoubleDown; };
	void SetDoubleDown(bool value) { m_bDidDoubleDown = value; };

	void ParseInput();
	void Play();
private:
	int m_bHit = false;
	int m_bDidDoubleDown = false;
};