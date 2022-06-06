#include "stdafx.h"
#include "Monster_Bullet.h"
#include "MushroomMonster.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"


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
	m_fSpeed = 0.05f;
}

void CMonsterBullet::Release()
{
}

int CMonsterBullet::Update()
{

	if (m_bDead)
	{
		if(m_eState == LEVEL3)
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMushroomMonster>::Create(m_tInfo.fX, m_tInfo.fY));

		return OBJ_DEAD;
	}
		

	Move();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonsterBullet::Late_Update()
{
	bool bBounce = false;
	float fY = 0.f;
	CLine* b_ColLine = CLineMgr::Get_Instance()->CollisionLine_Bullet(m_tInfo.fX, &fY);


	// Line Collision
	if (b_ColLine && m_tInfo.fY >= fY)
	{
		m_bDead = true;
	}
}

void CMonsterBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_eState == LEVEL3)
	{
		HBRUSH myBrush = nullptr;
		HBRUSH oldBrush = nullptr;

		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 235, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
	else
	{
		HBRUSH myBrush = nullptr;
		HBRUSH oldBrush = nullptr;

		myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}

}

void CMonsterBullet::Move(void)
{
	if (m_eState == LEVEL1)
	{
		m_fSpeed = 0.05f;
		m_tInfo.fX += m_tMovePoint.x*m_fSpeed;
		m_tInfo.fY -= m_tMovePoint.y*m_fSpeed;
	}
	else if (m_eState == LEVEL2)
	{
		m_fSpeed = 0.1f;
		m_tInfo.fX += m_tMovePoint.x*m_fSpeed;
		m_tInfo.fY -= m_tMovePoint.y*m_fSpeed;
	}
	else if (m_eState == LEVEL3)
	{
		m_fSpeed = 1.f;
		m_tInfo.fCX = 30;
		m_tInfo.fCY = 30;
		m_fAnimSpeed = 15.f;

		bool bBounce = false;
		float fY = 0.f;
		CLine* b_ColLine = CLineMgr::Get_Instance()->CollisionLine_Bullet(m_tInfo.fX, &fY);

		// No Line
		if (!b_ColLine)
		{
			m_bDead = true;
			/*m_tInfo.fY += m_fSpeed;
			m_tInfo.fX += Get_Dir() == DIR_RIGHT ? m_fSpeed : -m_fSpeed;*/
		}
		// Line
		else
		{
			// Line Collision
			if (m_tInfo.fY >= fY)
			{
				if (b_ColLine->Get_Line().fLPoint.fY < m_fBulletStartPosY || b_ColLine->Get_Line().fRPoint.fY < m_fBulletStartPosY)
				{
				
					m_bDead = true;
				}

				m_tInfo.fY = fY;
				bBounce = true;
			}

			m_tInfo.fY += m_fAnimSpeed * m_fAnimTime + (m_fAnimAccel * pow(m_fAnimTime, 2)) * 0.5f;
			m_fAnimTime += bBounce ? -0.2f : 0.03f;
			m_tInfo.fX += Get_Dir() == DIR_RIGHT ? m_fSpeed : -m_fSpeed;
			bBounce = false;
		}

	}

	
}


