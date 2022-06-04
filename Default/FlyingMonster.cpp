#include "stdafx.h"
#include "FlyingMonster.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "TurtleBack.h"
#include "TurtleMonster.h"
#include "Player.h"



CFlyingMonster::CFlyingMonster()
{
}


CFlyingMonster::~CFlyingMonster()
{
}

void CFlyingMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 40.f, 50.f };
	m_fSpeed = 1.5f;
}

int CFlyingMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bGet_Attacked)
	{
		if (!m_bCount)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTurtleMonster>::Create(m_tInfo.fX + 70, m_tInfo.fY));
			m_dwTime = GetTickCount();
			m_bCount = true;
		}

	}

	Jumping();
	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CFlyingMonster::Late_Update(void)
{
	if (m_bGet_Attacked)
	{
		m_bDead = true;

	}

	
}

void CFlyingMonster::Release(void)
{
}

void CFlyingMonster::Render(HDC hDC)
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

		Rectangle(hDC, m_tRect.left - 20, m_tRect.top + 20, m_tRect.right - 40, m_tRect.bottom - 20);
		Rectangle(hDC, m_tRect.left + 40, m_tRect.top + 20, m_tRect.right + 20, m_tRect.bottom - 20);

	}
	else
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CFlyingMonster::Move(void)
{
	m_tInfo.fY += m_fSpeed;

	if (m_tInfo.fY >= 500 || m_tInfo.fY < 200)
	{
		m_fSpeed *= -1;
	}
}

void CFlyingMonster::Jumping(void)
{
}
