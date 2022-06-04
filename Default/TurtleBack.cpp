#include "stdafx.h"
#include "TurtleBack.h"
#include "LineMgr.h"

CTurtleBack::CTurtleBack()
{
}


CTurtleBack::~CTurtleBack()
{
	Release();
}

void CTurtleBack::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 40.f, 40.f };
	m_fSpeed = 5.f;
}
int  CTurtleBack::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CTurtleBack::Late_Update(void)
{
	if (m_tRect.right > WINCX - 50 || m_tRect.left < 50)
	{
		m_fSpeed *= -1.f;
	}

	if (m_tRect.bottom > WINCY - 50 || m_tRect.top < 50)
	{
		m_fSpeed *= -1.f;
	}

	if (m_bGet_Attacked)
		m_bDead = true;


}

void CTurtleBack::Release(void)
{

}

void CTurtleBack::Render(HDC hDC)
{
	HBRUSH myBrush = nullptr;
	HBRUSH oldBrush = nullptr;

	myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 200, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

}


void CTurtleBack::Move(void)
{
	float fY = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);

	if (b_LineCol)
	{

		if (m_bFalling)
		{
			m_tInfo.fY += m_fSpeed;
			if (m_tInfo.fY >= fY - m_tInfo.fCY*0.5f)
				m_bFalling = false;
		}
		else
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;

		m_tInfo.fX += m_fSpeed;

	}
	else
	{
		m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}


}

