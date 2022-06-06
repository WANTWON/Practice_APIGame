#include "stdafx.h"
#include "Flower.h"
#include "LineMgr.h"
#include "ScrollMgr.h"

CFlower::CFlower()
{

}

CFlower::~CFlower()
{
	Release();
}

void CFlower::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;
}

void CFlower::Release()
{

}

int CFlower::Update()
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

void CFlower::Late_Update()
{
	
}

void CFlower::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + iScrollX, (int)m_tInfo.fY - 20);
	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top - 20, m_tRect.right + iScrollX, m_tRect.bottom - 20);
}

void CFlower::Animate()
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
}