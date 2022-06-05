#include "stdafx.h"
#include "BlockNull.h"


CBlockNull::CBlockNull()
	:m_ObjID(OBJ_END)
{
}


CBlockNull::~CBlockNull()
{
	Release();
}

void CBlockNull::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CBlockNull::Update(void)
{
	if (OBJ_DEAD == m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlockNull::Late_Update(void)
{
}

void CBlockNull::Release(void)
{
}

void CBlockNull::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
