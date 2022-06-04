#include "stdafx.h"
#include "CoinBlock.h"


CCoinBlock::CCoinBlock()
{
}


CCoinBlock::~CCoinBlock()
{
	Release();
}

int CCoinBlock::Update(void)
{
	if (OBJ_DEAD == m_bDead)
		return OBJ_DEAD;

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
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
