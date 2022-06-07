#include "stdafx.h"
#include "JumpingMonster.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "TurtleBack.h"
#include "TurtleMonster.h"
#include "Player.h"
#include "ScrollMgr.h"


CJumpingMonster::CJumpingMonster() : m_fTime(0), m_bJump(true)
{
}


CJumpingMonster::~CJumpingMonster()
{
}

void CJumpingMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 40.f, 50.f };
	m_fSpeed = 1.f;
	m_fJumpPower = 10.f;
	m_dwTime = GetTickCount();

	m_iType = MONSTER_JUMPING;
}

int CJumpingMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (false == m_bEditMode)
	{
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
	}



	Update_Rect();

	return OBJ_NOEVENT;
}

void CJumpingMonster::Late_Update(void)
{
	if (m_bGet_Attacked)
	{
		m_bDead = true;

	}

	if (m_dwTime + 2000 < GetTickCount() && m_tInfo.fY+ m_tInfo.fCY*0.5 >= fY)
	{
		if (m_bJump == true)
			m_bJump = false;
		else
			m_bJump = true;

		m_dwTime = GetTickCount();
	}

	CCollisionMgr::Collision_Bullet(this, CObjMgr::Get_Instance()->Get_Bullets());

}

void CJumpingMonster::Release(void)
{
}

void CJumpingMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_bGet_Attacked == false)
	{
		HBRUSH myBrush = nullptr;
		HBRUSH oldBrush = nullptr;

		myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 200, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);

		Rectangle(hDC, m_tRect.left-20 + iScrollX, m_tRect.top+20, m_tRect.right-40 + iScrollX, m_tRect.bottom-20);
		Rectangle(hDC, m_tRect.left + 40 + iScrollX, m_tRect.top + 20, m_tRect.right + 20 + iScrollX, m_tRect.bottom - 20);

	}
	else
	{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}

}

void CJumpingMonster::Move(void)
{
	
	 fY = 0.f;

	bool b_LineCol = CLineMgr::Get_Instance()->CollisionLine(m_tInfo.fX, m_tInfo.fY, &fY);

	if (b_LineCol)
	{
		
		
		if (m_tInfo.fY > fY)
		{
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
			m_fTime = 0.f;
		}
			
		
	}
	else
	{
		m_fSpeed *= -1;
		m_tInfo.fX += m_fSpeed;
	}
}

void CJumpingMonster::Jumping(void)
{
	if (m_bJump )//&& dynamic_cast<CPlayer*>(m_pTarget)->Get_bJump() )
	{
		m_tInfo.fY -= m_fJumpPower*m_fTime - (9.8f*m_fTime*m_fTime*0.5f);
		m_fTime += 0.1f;

		if (m_pTarget)
		{
			if (m_pTarget->Get_Info().fX > m_tInfo.fX)
				m_tInfo.fX += m_fSpeed;
			else
				m_tInfo.fX -= m_fSpeed;

		}

	}
	else
	{
		if (m_pTarget)
		{
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
			if (m_pTarget->Get_Info().fX > m_tInfo.fX)
				m_tInfo.fX += m_fSpeed;
			else
				m_tInfo.fX -= m_fSpeed;
			
		}
		else
			m_tInfo.fX += m_fSpeed;
	}

}
