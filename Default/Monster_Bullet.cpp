#include "stdafx.h"
#include "Monster_Bullet.h"
#include "LineMgr.h"


CMonsterBullet::CMonsterBullet() 
{
}


CMonsterBullet::~CMonsterBullet()
{
}

void CMonsterBullet::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 0.1f;
}

void CMonsterBullet::Release()
{
}

int CMonsterBullet::Update()
{

	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_tMovePoint.x*m_fSpeed;
	m_tInfo.fY -= m_tMovePoint.y*m_fSpeed;


	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonsterBullet::Late_Update()
{
	bool bBounce = false;
	float fY = 0.f;
	CLine* b_ColLine = CLineMgr::Get_Instance()->CollisionLine_Bullet(m_tInfo.fX, m_tInfo.fY, &fY);


	// Line Collision
	if (b_ColLine && m_tInfo.fY >= fY)
	{

		m_bDead = true;
	}
}

void CMonsterBullet::Render(HDC hDC)
{
	HBRUSH myBrush = nullptr;
	HBRUSH oldBrush = nullptr;

	myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}
