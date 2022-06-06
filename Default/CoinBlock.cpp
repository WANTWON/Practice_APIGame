#include "stdafx.h"
#include "CoinBlock.h"
#include "ScrollMgr.h"

CCoinBlock::CCoinBlock()
	:m_bUsed(false)
{
}


CCoinBlock::~CCoinBlock()
{
	Release();
}

void CCoinBlock::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_BlockType = BLOCK_COIN;
	m_bItem = true;
}

int CCoinBlock::Update(void)
{
	
	if (OBJ_DEAD == m_bDead)
	{
		m_bUsed = true;

		m_bDead = OBJ_NOEVENT;
		return OBJ_NOEVENT;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCoinBlock::Late_Update(void)
{
}

void CCoinBlock::Release(void)
{
}

void CCoinBlock::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (false == m_bUsed)
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
	else
	{
		//	юс╫ц
		Rectangle(hDC, m_tRect.left + iScrollX+ 10.f, m_tRect.top + 10.f, m_tRect.right - 10.f + iScrollX, m_tRect.bottom - 10.f);
	}

	TextOut(hDC, m_tInfo.fX, m_tInfo.fY, L"C", DT_CENTER);
}
