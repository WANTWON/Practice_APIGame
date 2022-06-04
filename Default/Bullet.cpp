#include "stdafx.h"
#include "Bullet.h"
#include "LineMgr.h"

// Bullet:
// .Should bounce on horizontal surfaces;
// .Should be destroyed on collision with vertical surfaces;
// .Should be destroyed on collision with monsters;
// .Should be destroyed when exiting the screen space.

CBullet::CBullet() : m_fAnimSpeed(0.f), m_fAnimTime(0.f), m_fAnimAccel(9.8f)
{
}

CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;

	m_fAnimSpeed = 10.f;
}

void CBullet::Release()
{
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (Get_Dir() == DIR_RIGHT)
	{
		float fY = 0.f;
		bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, &fY);

		

		m_tInfo.fY += m_fAnimSpeed * m_fAnimTime + (m_fAnimAccel * pow(m_fAnimTime, 2)) * 0.5f;
		m_fAnimTime += 0.01f;

		m_tInfo.fX += m_fSpeed;
	}
		
	else if (Get_Dir() == DIR_LEFT)
	{
		float fY = 0.f;
		CLine line;

		bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine_Bullet(m_tInfo.fX, m_tInfo.fY, &fY, &line);
		
		m_tInfo.fY += m_fAnimSpeed * m_fAnimTime + (m_fAnimAccel * pow(m_fAnimTime, 2)) * 0.5f;
		m_fAnimTime += 0.01f;

		m_tInfo.fX -= m_fSpeed;
	}
	
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	
}

void CBullet::Render(HDC hDC)
{
	HBRUSH myBrush = nullptr;
	HBRUSH oldBrush = nullptr;

	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); 

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}
