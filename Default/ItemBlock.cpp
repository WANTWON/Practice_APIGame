#include "stdafx.h"
#include "ItemBlock.h"


CItemBlock::CItemBlock()
{
}


CItemBlock::~CItemBlock()
{
	Release();
}

int CItemBlock::Update(void)
{
	if (OBJ_DEAD == m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CItemBlock::Late_Update(void)
{
}

void CItemBlock::Release(void)
{
}

void CItemBlock::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
