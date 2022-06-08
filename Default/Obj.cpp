#include "stdafx.h"
#include "Obj.h"
#include "StageMgr.h"
#include "UIMgr.h"

CObj::CObj() : m_bDead(false), m_fSpeed(0.f), m_bDead_Count(false), m_bBye(false), m_iPoints_Given(0), m_iCoins_Given(0), m_bEditMode(false), m_dwDrawTime(GetTickCount()), DrawID(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = int(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.right = int(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.top = int(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.bottom = int(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Set_Dead(bool _dead, bool b_JustDie)
{
	m_bDead = _dead;

	if (!b_JustDie)
	{
		CStageMgr* StageMgr = CStageMgr::Get_Instance();
		StageMgr->Increment_Score(m_iPoints_Given);
		StageMgr->Increment_Coins(m_iCoins_Given);

		if (m_iPoints_Given != 0)
		{
			CPointNumbers* pPointNumbers = new CPointNumbers(m_iPoints_Given, m_tInfo.fX, m_tInfo.fY);
			CUIMgr::Get_Instance()->Add(pPointNumbers);
		}
	}
}
