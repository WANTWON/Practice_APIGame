#include "stdafx.h"
#include "TurtleMonster.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "TurtleBack.h"


CTurtleMonster::CTurtleMonster() 
{
}


CTurtleMonster::~CTurtleMonster()
{
	Release();
}

void CTurtleMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 40.f, 50.f };
	m_fSpeed = 2.f;
}
int  CTurtleMonster::Update(void)
{
	

	if (m_bGet_Attacked)
	{
		m_tInfo.fCY = 25;
		
		if (!m_bCount)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleBack>::Create(m_tInfo.fX+50, m_tInfo.fY));
			m_dwTime = GetTickCount();
			m_fSpeed *= 0.5f;
			m_bCount = true;
		}

	}

	if (m_bDead)
		return OBJ_DEAD;

	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CTurtleMonster::Late_Update(void)
{
	if (m_tRect.right > WINCX - 50 || m_tRect.left < 50)
	{
		m_fSpeed *= -1.f;
	}

	if (m_tRect.bottom > WINCY - 50 || m_tRect.top < 50)
	{
		m_fSpeed *= -1.f;
	}


	if (m_bGet_Attacked )//&& m_dwTime + 500 < GetTickCount())
	{
			m_bDead = true;
		
	}


}

void CTurtleMonster::Release(void)
{

}

void CTurtleMonster::Render(HDC hDC)
{

	if (m_bGet_Attacked == false)
	{
		HBRUSH myBrush = nullptr;
		HBRUSH oldBrush = nullptr;

		myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 200, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
	else
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

}


void CTurtleMonster::Move(void)
{
	float fY = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);

	if (b_LineCol)
	{

		if (m_bFalling)
		{
			m_tInfo.fY += m_fSpeed*1.3f;
			if (m_tInfo.fY >= fY - m_tInfo.fCY*0.5f)
				m_bFalling = false;
		}
		else
		{
			m_tInfo.fX += m_fSpeed;
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
		}
	}
	else
	{
		m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}


}
