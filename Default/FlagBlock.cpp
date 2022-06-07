#include "stdafx.h"
#include "FlagBlock.h"
#include "ScrollMgr.h"

CFlagBlock::CFlagBlock()
	: m_bNumber(false), m_iDown(0), m_fCount(0)
{
}


CFlagBlock::~CFlagBlock()
{
	Release();
	
}


void CFlagBlock::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 15.f;
}

int CFlagBlock::Update(void)
{
	if (OBJ_DEAD == m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CFlagBlock::Late_Update(void)
{
	if (1 == m_iDown)
	{
		m_fCount += 0.5f;
		m_tInfo.fY += 1.f;
		if (160.f <= m_fCount)
		{
			m_iDown = 0;
		}
	}

}

void CFlagBlock::Release(void)
{
}

void CFlagBlock::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}
