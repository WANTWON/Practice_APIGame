#include "stdafx.h"
#include "Mushroom.h"
#include "LineMgr.h"
#include "ScrollMgr.h"

CMushroom::CMushroom()
{

}

CMushroom::~CMushroom()
{
	Release();
}

void CMushroom::Initialize()
{
	m_tInfo.fCX = 25.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 2.f;

	m_fAnimSpeed = 15.f;
}

void CMushroom::Release()
{

}

int CMushroom::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	if (false == m_bEditMode)
	{
		Animate();
	}



	Update_Rect();

	return OBJ_NOEVENT;
}

void CMushroom::Late_Update()
{

}

void CMushroom::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CMushroom::Animate()
{
	if (m_bIsSpawned)
	{
		float fY = 0.f;
		bool bLineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);

		if (bLineCol)
		{
			// Fall
			if (m_tInfo.fY < fY)
				m_tInfo.fY += m_fSpeed;

			// Move
			if (m_tInfo.fY >= fY)
			{
				m_tInfo.fY = fY;
				m_tInfo.fX += m_fSpeed;
			}
		}
		else
		{
			m_fSpeed *= -1;
			m_tInfo.fX += m_fSpeed;
		}
	}
	else
	{
		// Spawn
		m_tInfo.fY -= m_fSpeed / 10;

		if (GetTickCount() > m_dwTime + 1000)
		{
			m_bIsSpawned = true;
		}
	}
}