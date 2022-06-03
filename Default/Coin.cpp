#include "stdafx.h"
#include "Coin.h"


CCoin::CCoin()
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
}

void CCoin::Release()
{
}

int CCoin::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Animate();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCoin::Late_Update()
{

}

void CCoin::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CCoin::Animate()
{
	// Bounce
	m_tInfo.fY -= m_fAnimSpeed * m_fAnimTime - 0.5f * (pow(m_fAnimTime, 2) * m_fAnimAccel);
	m_fAnimTime += .2f;

	if (GetTickCount() > m_dwTime + 325)
		m_bDead = true;

	// TODO:
	// Destroy on collision with source block (not based on time).
}
