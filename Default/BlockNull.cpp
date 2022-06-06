#include "stdafx.h"
#include "BlockNull.h"


CBlockNull::CBlockNull()
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
	HBRUSH myBrush = nullptr;
	HBRUSH oldBrush = nullptr;

	myBrush = (HBRUSH)CreateSolidBrush(RGB(245, 245, 245));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	
}
