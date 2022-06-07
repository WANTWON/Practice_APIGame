#include "stdafx.h"
#include "Coin.h"
#include "ScrollMgr.h"

CCoin::CCoin() : m_bIsBlockItem(false)
{

}

CCoin::~CCoin()
{
	Release();
}

void CCoin::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;
	m_fAnimSpeed = 15.f;
	
	m_iPoints_Given = 200;
	m_iCoins_Given = 1;

	// Is a Coin spawned from a Block
	if (m_Type == ITEM_COIN)
		m_bIsBlockItem = true; // If FALSE, is a Coin placed in the Level
}

void CCoin::Release()
{

}

int CCoin::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bIsBlockItem)
		Animate();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCoin::Late_Update()
{

}

void CCoin::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HBRUSH myBrush = nullptr;
	HBRUSH oldBrush = nullptr;

	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);	
}

void CCoin::Animate()
{
	// Bounce
	m_tInfo.fY -= m_fAnimSpeed * m_fAnimTime - 0.5f * (pow(m_fAnimTime, 2) * m_fAnimAccel);
	m_fAnimTime += .2f;

	// TODO:
	// Destroy on collision with source block (not based on time).
	if (GetTickCount() > m_dwTime + 325)
		Set_Dead(true);
}
