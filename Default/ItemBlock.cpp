#include "stdafx.h"
#include "ItemBlock.h"


CItemBlock::CItemBlock()
{
}


CItemBlock::~CItemBlock()
{
	Release();
}

void CItemBlock::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_bItem = true;
}

int CItemBlock::Update(void)
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
