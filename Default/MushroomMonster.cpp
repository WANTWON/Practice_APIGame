#include "stdafx.h"
#include "LineMgr.h"
#include "MushroomMonster.h"


CMushroomMonster::CMushroomMonster()
{
}


CMushroomMonster::~CMushroomMonster()
{
	Release();
}



void CMushroomMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 40.f, 40.f };
	m_fSpeed = 1.f;
}
int  CMushroomMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Attacked)
	{
		m_iMonsterNumder = 1;
		m_bDead = true;

	/*	if (!m_bCount)
		{
			m_dwTime = GetTickCount();
			m_bCount = true;
		}*/
	}
	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMushroomMonster::Late_Update(void)
{
	if (m_tRect.right > WINCX - 50 || m_tRect.left < 50)
	{
		m_fSpeed *= -1.f;
	}

	if (m_tRect.bottom > WINCY - 50 || m_tRect.top < 50)
	{
		m_fSpeed *= -1.f;
	}

	/*if (m_bGet_Attacked && m_dwTime + 500 < GetTickCount())
		m_bDead = true;*/

}

void CMushroomMonster::Release(void)
{

}

void CMushroomMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}


void CMushroomMonster::Move(void)
{
	float fY = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(this, &fY);

	if (b_LineCol)
	{

		if (m_bFalling)
		{
			m_tInfo.fY += m_fSpeed;
			if (m_tInfo.fY >= fY - m_tInfo.fCY*0.5f)
				m_bFalling = false;
		}
		else
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;

		m_tInfo.fX += m_fSpeed;

	}
	else
	{
		m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}


}
