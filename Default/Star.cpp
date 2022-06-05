#include "stdafx.h"
#include "Star.h"
#include "LineMgr.h"
#include "Line.h"

CStar::CStar()
{

}

CStar::~CStar()
{
	Release();
}

void CStar::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;
	m_fAnimSpeed = 10.f;
}

void CStar::Release()
{

}

int CStar::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Animate();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CStar::Late_Update()
{

}

void CStar::Render(HDC hDC)
{
	MoveToEx(hDC, m_tInfo.fX - 10.f, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX + 10.f, m_tInfo.fY);
	LineTo(hDC, m_tInfo.fX - 5.f, m_tInfo.fY + 10.f);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY - 8.f);
	LineTo(hDC, m_tInfo.fX + 5.f, m_tInfo.fY + 10.f);
	LineTo(hDC, m_tInfo.fX - 10.f, m_tInfo.fY);
}

void CStar::Animate()
{
	if (!m_bIsSpawned)
	{
		// Spawn
		m_tInfo.fY -= m_fSpeed / 10;

		if (GetTickCount() > m_dwTime + 1000)
		{
			m_bIsSpawned = true;
		}
	}
	else
	{
		bool bBounce = false;
		float fY = 0.f;

		CLine* b_ColLine = CLineMgr::Get_Instance()->CollisionLine_Bullet(m_tInfo.fX, &fY);

		// Line
		if (b_ColLine)
		{
			// Line Collision
			if (m_tInfo.fY >= fY)
			{
				bBounce = true;
				m_tInfo.fY = fY;
			}

			m_tInfo.fY += m_fAnimSpeed * m_fAnimTime + (m_fAnimAccel * pow(m_fAnimTime, 2)) * 0.5f;
			m_fAnimTime += bBounce ? -0.2 : 0.01f;
			m_tInfo.fX += m_fSpeed;
			bBounce = false;
		}
		// No Line
		else
		{
			m_fSpeed *= -1;
			m_tInfo.fX += m_fSpeed;
		}
	}
}